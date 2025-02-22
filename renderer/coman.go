package renderer

import (
	"fmt"
	"regexp"
	"strconv"
	"strings"
	"time"

	"github.com/g3n/engine/gls"
)

// Regular expression to parse #include <name> [quantity] directive
func init() {

	rexInclude = regexp.MustCompile(`#include\s+<(.*)>\s*(?:\[(.*)]|)`)
}

// A simplified version of map[string]shaders.ProgramInfo - instead of listing
// multiple shaders due to multiple types, this type only has to map program
// names to compute shader names
type ShadersOfProgram map[string]string

// Coman is a sibling of Shaman
type Coman struct { // Command Manager
	gs        *gls.GLS
	includes  map[string]string      // include files sources
	shadercm  map[string]string      // maps shader name to its template
	proginfo  ShadersOfProgram       // maps name of the program to name of its shader
	programs  []gls.ComputeProgSpecs // list of compiled programs with specs
	progSpecs gls.ComputeProgSpecs   // Current program specs
	//stats Stats <- maybe something for the future
}

// NewComan creates and returns a pointer to a new Coman.
func NewComan(gs *gls.GLS) *Coman {
	cm := new(Coman)
	cm.Init(gs)
	return cm
}

// Init initializes a compute shader
func (cm *Coman) Init(gs *gls.GLS) {
	cm.gs = gs
	cm.includes = make(map[string]string)
	cm.shadercm = make(map[string]string)
	cm.proginfo = make(ShadersOfProgram)
}

func (cm *Coman) GLS() *gls.GLS { return cm.gs }

// AddShader adds a shader program with the specified name and source code
func (cm *Coman) AddShader(name, source string) {
	cm.shadercm[name] = source
}

// AddProgram adds a program with the specified name and associated compute
// shader name
func (cm *Coman) AddProgram(programName, computeShaderName string) {
	cm.proginfo[programName] = computeShaderName
}

// Delete a program from OpenGL. Return true iff program was found and deleted
func (cm *Coman) DeleteProgram(s *gls.ComputeSpecs) bool {
	for _, pinfo := range cm.programs {
		if pinfo.Specs.Equals(s) {
			pinfo.Program.Delete()
			return true
		}
	}
	return false
}

// SetProgram sets the shader program to satisfy the specified specs.
// Returns an indication if the current shader has changed and a possible error
// when creating a new shader program.
func (cm *Coman) SetProgram(s *gls.ComputeSpecs) (bool, error) {

	var specs gls.ComputeSpecs
	specs.Copy(s)
	if cm.progSpecs.Specs.Equals(&specs) {
		if !cm.progSpecs.Program.InUse() {
			cm.progSpecs.Specs = specs
			cm.gs.UseProgram(cm.progSpecs.Program)
			return true, nil
		}
		return false, nil
	}

	// Search for compiled program with the specified specs
	for _, pinfo := range cm.programs {
		if pinfo.Specs.Equals(&specs) {
			cm.progSpecs = pinfo
			cm.gs.UseProgram(pinfo.Program)
			return true, nil
		}
	}

	// Generates new program with the specified specs
	prog, err := cm.GenProgram(&specs)
	if err != nil {
		return false, err
	}
	log.Debug("Created new compute shader:%v", specs.Name)

	// Save specs as current specs, adds new program to the list and activates the program
	cm.progSpecs = gls.ComputeProgSpecs{prog, specs}
	cm.programs = append(cm.programs, cm.progSpecs)
	err = specs.BufferObjects.Bind(cm.gs) //prepare buffer objects before using the program
	if err != nil {
		return false, err
	}
	cm.gs.UseProgram(prog)
	return true, nil
}

// GenProgram generates a shader program from the specified shader
func (cm *Coman) GenProgram(specs *gls.ComputeSpecs) (*gls.Program, error) {
	shaderName, ok := cm.proginfo[specs.Name]
	if !ok {
		return nil, fmt.Errorf("Program:%s not found", specs.Name)
	}
	defines := map[string]string{}
	for name, value := range specs.Defines {
		defines[name] = value
	}
	computeSource, ok := cm.shadercm[shaderName]
	if !ok {
		return nil, fmt.Errorf("Compute shader:%s not found", shaderName)
	}
	// Pre-process vertex shader source
	computeSource, err := cm.preprocess(computeSource, defines)
	if err != nil {
		return nil, err
	}

	prog := cm.gs.NewProgram()
	prog.AddShader(gls.COMPUTE_SHADER, computeSource)
	err = prog.Build()
	if err != nil {
		return nil, err
	}

	return prog, nil
}

func (cm *Coman) preprocess(source string, defines map[string]string) (string, error) {

	// If defines map supplied, generate prefix with glsl version directive first,
	// followed by "#define" directives
	var prefix = ""
	if defines != nil { // This is only true for the outer call
		prefix = fmt.Sprintf("#version %s\n", GLSL_VERSION)
		for name, value := range defines {
			prefix = prefix + fmt.Sprintf("#define %s %s\n", name, value)
		}
	}

	return cm.processIncludes(prefix+source, defines)
}

// preprocess preprocesses the specified source prefixing it with optional defines directives
// contained in "defines" parameter and replaces '#include <name>' directives
// by the respective source code of include chunk of the specified name.
// The included "files" are also processed recursively.
func (cm *Coman) processIncludes(source string, defines map[string]string) (string, error) {

	// Find all string submatches for the "#include <name>" directive
	matches := rexInclude.FindAllStringSubmatch(source, 100)
	if len(matches) == 0 {
		return source, nil
	}

	// For each directive found, replace the name by the respective include chunk source code
	//var newSource = source
	for _, m := range matches {
		incFullMatch := m[0]
		incName := m[1]
		incQuantityVariable := m[2]

		// Get the source of the include chunk with the match <name>
		incSource := cm.includes[incName]
		if len(incSource) == 0 {
			return "", fmt.Errorf("Include:[%s] not found", incName)
		}

		// Preprocess the include chunk source code
		incSource, err := cm.processIncludes(incSource, defines)
		if err != nil {
			return "", err
		}

		// Skip line
		incSource = "\n" + incSource

		// Process include quantity variable if provided
		if incQuantityVariable != "" {
			incQuantityString, defined := defines[incQuantityVariable]
			if defined { // Only process #include if quantity variable is defined
				incQuantity, err := strconv.Atoi(incQuantityString)
				if err != nil {
					return "", err
				}
				// Check for iterated includes and populate index parameter
				if incQuantity > 0 {
					repeatedIncludeSource := ""
					for i := 0; i < incQuantity; i++ {
						// Replace all occurrences of the index parameter with the current index i.
						repeatedIncludeSource += strings.Replace(incSource, indexParameter, strconv.Itoa(i), -1)
					}
					incSource = repeatedIncludeSource
				}
			} else {
				incSource = ""
			}
		}

		// Replace all occurrences of the include directive with its processed source code
		source = strings.Replace(source, incFullMatch, incSource, -1)
	}
	return source, nil
}

// Dispatch the compute shader program previously set with SetProgram and
// process all corresponding buffer objects
func (cm *Coman) Compute(nWorkGroups gls.NumWorkGroups, deltaTime time.Duration) error {
	cm.gs.DispatchCompute(nWorkGroups)
	cm.gs.MemoryBarrier(gls.SHADER_STORAGE_BARRIER_BIT) // Ensure data is written before reading
	err := cm.progSpecs.Specs.BufferObjects.Process(cm.gs, deltaTime)
	return err
}
