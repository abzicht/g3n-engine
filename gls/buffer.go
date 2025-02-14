package gls

import (
	"time"
	"unsafe"
)

type NumWorkGroups struct {
	X uint32 // number of work groups in x axis
	Y uint32 // number of work groups in y axis
	Z uint32 // number of work groups in z axis
}

func NewNumWorkGroups(x, y, z uint32) *NumWorkGroups {
	n := new(NumWorkGroups)
	n.X = x
	n.Y = y
	n.Z = z
	return n
}

type BufferObject interface {
	// Returns the id that gls uses to identify this buffer
	GetBufferID() uint32
	// Binds this buffer to the provided gls
	Bind(gs *GLS)
	// Process the data held in buffer locally by passing it to the provided callback
	Process(gs *GLS, deltaTime time.Duration)
	// Deletes this buffer from the provided gls
	Delete(gs *GLS)
}

// ProcessCallback is called within SSBO.Process and receives a pointer to the
// buffer as well as a reference to SSBO itself.
// This function must finish reading / writing to p before it returns
// Note to end user: make good use of closures!
type ProcessCallback func(ssbo *SSBO, p unsafe.Pointer, deltaTime time.Duration)

type AccessType int

// Access Type with that glMapBuffer is called by SSBO
const (
	SSBO_READ_ONLY  AccessType = READ_ONLY
	SSBO_WRITE_ONLY AccessType = WRITE_ONLY
	SSBO_READ_WRITE AccessType = READ_WRITE
)

// Shader Storage Buffer Object (SSBO) can be shared by program memory and
// compute shaders
type SSBO struct {
	// ID that GLS uses to identify this object
	BufferID uint32
	// binding index must match a binding in the shader.
	/*
	 * For index 3, the following format would be used in the shader:
	 * layout(std430, binding = 3) buffer layoutName
	 *  { int data_SSBO[]; };
	 */
	BindingIndex uint32
	// Access type with that SSBO.Process reads / writes the buffer
	Access          AccessType
	ProcessCallback ProcessCallback
	// Data type found in the buffer
	DataType int
	// Number of elements in the buffer
	Length int
}

// Create a new SSBO that binds to a shader variable identified with bindingIndex
// The SSBO buffer will contain length elements of type dataType
// E.g., NewSSBO(gs, 0, float32, 4) results in a shared buffer of size
// 4 * 32 bytes
// Creating a new ssbo does not yet create the buffer in GLS. For that,
// ssbo.GenBuffer must be called once.
func NewSSBO(gs *GLS, bindingIndex uint32, access AccessType, processCallback ProcessCallback, dataType int, length int) *SSBO {
	s := new(SSBO)
	s.Init(gs, bindingIndex, access, processCallback, dataType, length)
	return s
}

func (s *SSBO) Init(gs *GLS, bindingIndex uint32, access AccessType, processCallback ProcessCallback, dataType int, length int) {
	s.BindingIndex = bindingIndex
	s.Access = access
	s.ProcessCallback = processCallback
	s.DataType = dataType
	s.Length = length
	s.BufferID = gs.GenBuffer()
}

// Return the buffer id in GLS that this ssbo references
func (s *SSBO) GetBufferID() uint32 {
	return s.BufferID
}

// Binds this SSBO's GLS buffer to the provided GLS instance
func (s *SSBO) Bind(gs *GLS) {
	gs.BindBuffer(SHADER_STORAGE_BUFFER, s.BufferID)
	// initialize buffer with correct length but no data
	// future: replace nil with optional pointer to data?
	gs.NamedBufferData(s.BufferID, uint32(unsafe.Sizeof(s.DataType)*uintptr(s.Length)), nil, DYNAMIC_COPY)
	gs.BindBufferBase(SHADER_STORAGE_BUFFER, s.BindingIndex, s.BufferID) // Bind to binding point found in shader
	gs.BindBuffer(SHADER_STORAGE_BUFFER, 0)                              // value 0 indicates: unbind!
}

func (s *SSBO) Process(gs *GLS, deltaTime time.Duration) {
	gs.BindBuffer(SHADER_STORAGE_BUFFER, s.BufferID)
	ptr := gs.MapNamedBuffer(s.BufferID, int(s.Access))
	if ptr != uintptr(0) {
		data := (unsafe.Pointer(ptr))
		s.ProcessCallback(s, data, deltaTime)
		gs.UnmapNamedBuffer(s.BufferID)
	}
	gs.BindBuffer(SHADER_STORAGE_BUFFER, 0) // unbind this buffer, clearing data
}

func (s *SSBO) Delete(gs *GLS) {
	gs.DeleteBuffers(s.BufferID)
}

type PBO struct { // Pixel Buffer Object
	// Make this implement the BufferObject interface
}

type BufferObjects map[uint32]BufferObject

// NewBufferObjects creates and returns a pointer to a BufferObjects object.
func NewBufferObjects() *BufferObjects {
	b := BufferObjects(make(map[uint32]BufferObject))
	return &b
}

// Returns a BufferObject identified by the provided id
func (b *BufferObjects) Get(id uint32) BufferObject {
	return (*b)[id].(BufferObject)
}

// Returns all BufferObject values held by b
func (b *BufferObjects) Values() []BufferObject {
	var entries []BufferObject
	for _, entry := range map[uint32]BufferObject(*b) {
		entries = append(entries, entry)
	}
	return entries
}

// Set sets a buffer object with its given id
func (b *BufferObjects) Set(bo BufferObject) {
	(*b)[bo.GetBufferID()] = bo
}

// Unset removes the specified buffer object.
func (b *BufferObjects) Unset(id uint32) {

	delete(*b, id)
}

// Add adds to this BufferObjects all the key-value pairs in the specified BufferObjects.
func (b *BufferObjects) Add(other *BufferObjects) {

	for k, v := range map[uint32]BufferObject(*other) {
		(*b)[k] = v
	}
}

// Equals compares two BufferObjects and returns true if they contain the same key-value pairs.
func (b *BufferObjects) Equals(other *BufferObjects) bool {

	if b == nil && other == nil {
		return true
	}
	if b != nil && other != nil {
		if len(*b) != len(*other) {
			return false
		}
		for k := range map[uint32]BufferObject(*b) {
			v1, ok1 := (*b)[k]
			v2, ok2 := (*other)[k]
			if v1 != v2 || ok1 != ok2 {
				return false
			}
		}
		return true
	}
	// One is nil and the other is not nil
	return false
}

// Binds all buffer objects so that the next used program can access
// these.
func (b *BufferObjects) Bind(gs *GLS) {
	for _, bufferObject := range map[uint32]BufferObject(*b) {
		bufferObject.Bind(gs)
	}
}

// Calls Process for all buffer objects
func (b *BufferObjects) Process(gs *GLS, deltaTime time.Duration) {
	for _, bufferObject := range map[uint32]BufferObject(*b) {
		bufferObject.Process(gs, deltaTime)
		//TODO test if making this multithreaded is allowed & beneficial
	}
}

// Deletes all buffer objects from gls and removes those from the
// map
func (b *BufferObjects) DeleteBufferObjects(gs *GLS) {
	for id, bufferObject := range map[uint32]BufferObject(*b) {
		bufferObject.Delete(gs)
		(*b).Unset(id)
	}
}
