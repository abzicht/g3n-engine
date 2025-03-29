package gls

import (
	"errors"
	"fmt"
	"iter"
	"maps"
	"time"
	"unsafe"
)

type BufferObjects map[uint32]BufferObject

type BufferObject interface {
	// Returns the id that gls uses to identify this buffer
	BufferID() uint32
	// Binds this buffer to the provided gls
	Bind(gs *GLS) error
	// Process the data held in buffer locally
	Process(gs *GLS, deltaTime time.Duration) error
	// Deletes this buffer from the provided gls
	Delete(gs *GLS)
}

// Shader Storage Buffer Object (SSBO) can be shared between CPU and compute
// shaders as well as between compute shaders and other types of shaders.
type SSBO struct {
	gs *GLS
	// ID that GLS uses to identify this object
	bufferID uint32
	// Usage type with that SSBO.Bind initializes the buffer
	Usage BOUsageType
	/* BindingIndex must match a buffer's binding in the shader.
	 * For index 3, the following format would be used in the shader:
	 * layout(std430, binding = 3) buffer BufferName
	 *  { int data_SSBO[]; };
	 */
	BindingIndex uint32
	// Access type with that SSBO.Process reads / writes the buffer
	Access BOAccessType
	// Callback that is called with the buffer data obtained from GLS
	// Set to nil in order to skip the CPU processing step
	SSBOCallback  SSBOCallback
	initialBuffer *BufferRaw
}

// SSBOCallback is called within SSBO.Process and receives a BufferRaw object.
// This function must finish reading / writing to the buffer before it returns,
// otherwise, the shader won't take note of further updates to the buffer
// Note to end user: make good use of closures and use the correct BOAccessType!
type SSBOCallback func(b *BufferRaw, deltaTime time.Duration)

// Create a new SSBO of the given size that binds to a shader storage block
// identified with its binding index.
// The ssboCallback is called by (*SSBO).Process and receives the current
// buffer state. ssboCallback can apply changes on the buffer and reflect those
// to the shader, but only, if access is set to BO_WRITE_ONLY or
// BO_READ_WRITE.
// Use (*SSBO).SetInitialBuffer to prefill the buffer before the first call to
// Process.
// Set usage to DYNAMIC_COPY / DYNAMIC_DRAW when expecting to modify this buffer's contents
func NewSSBO(gs *GLS, bindingIndex uint32, usage BOUsageType, access BOAccessType, ssboCallback SSBOCallback, size uint32) *SSBO {
	s := new(SSBO)
	s.Init(gs, bindingIndex, usage, access, ssboCallback, uint32(size))
	return s
}

// Initialize SSBO
func (s *SSBO) Init(gs *GLS, bindingIndex uint32, usage BOUsageType, access BOAccessType, ssboCallback SSBOCallback, size uint32) {
	s.BindingIndex = bindingIndex
	s.Usage = usage
	s.Access = access
	s.SSBOCallback = ssboCallback
	s.initialBuffer = NewBufferRaw(nil, size)
	s.bufferID = gs.GenBuffer()
}

// Set the initial buffer data to the contents of the provided buffer.
// This function is only effective when called before s.Bind() where the data
// is being applied. This function also overwrites updates the buffer size that
// will be used in Bind.
func (s *SSBO) SetInitialBuffer(buffer *BufferRaw) *SSBO {
	if buffer.Address == nil || buffer.Size == 0 {
		panic("Trying to initialize SSBO with buffer that points to NIL")
	}
	if buffer.Size == 0 {
		panic("Trying to initialize SSBO with empty buffer")
	}
	s.initialBuffer.Address = buffer.Address
	s.initialBuffer.Size = buffer.Size
	return s
}

// Return the buffer id in GLS that this ssbo references
func (s *SSBO) BufferID() uint32 {
	return s.bufferID
}

// Binds this SSBO's GLS buffer to the provided GLS instance and, on first
// call, copies the
// data set with SetInitialBuffer to this buffer.
func (s *SSBO) Bind(gs *GLS) error {
	gs.BindBuffer(SHADER_STORAGE_BUFFER, s.bufferID)
	// Initialize buffer with the given size. If initialBuffer.Address is nil,
	// no data is copied, otherwise, the buffer's data is sent to GLS.
	gs.NamedBufferData(s.bufferID, s.initialBuffer.Size, s.initialBuffer.Address, uint32(s.Usage))
	gs.BindBufferBase(SHADER_STORAGE_BUFFER, s.BindingIndex, s.bufferID) // Bind to binding point found in shader
	gs.BindBuffer(SHADER_STORAGE_BUFFER, 0)                              // value 0 indicates: unbind!
	s.initialBuffer.Address = nil
	return nil
}

// Bind to the GLS buffer and call the user-defined callback on that
// buffer before unmapping and unbinding it.
// Does nothing if no callback is defined
func (s *SSBO) Process(gs *GLS, deltaTime time.Duration) error {
	if s.SSBOCallback != nil {
		gs.BindBuffer(SHADER_STORAGE_BUFFER, s.bufferID)
		ptr := gs.MapNamedBuffer(s.bufferID, int(s.Access))
		if ptr != uintptr(0) {
			s.SSBOCallback(NewBufferRaw(unsafe.Pointer(ptr), s.initialBuffer.Size), deltaTime)
			gs.UnmapNamedBuffer(s.bufferID)
		} else {
			return fmt.Errorf("Failed to obtain SSBO buffer from GLS using glMapNamedBuffer for buffer with id %d", s.bufferID)
		}
		gs.BindBuffer(SHADER_STORAGE_BUFFER, 0) // unbind this buffer, clearing data
	}
	return nil
}

// Find out this ssbo's binding index for a given program and return it
func (s *SSBO) bindingIndexFromProgram(gs *GLS, bufferName string, programHandle uint32) uint32 {
	ssboIndex := gs.GetProgramResourceIndex(programHandle, SHADER_STORAGE_BLOCK, bufferName)
	property := uint32(BUFFER_BINDING)
	var bI int32
	gs.GetProgramResourceiv(programHandle, SHADER_STORAGE_BLOCK, ssboIndex, 1, &property, 1, nil, &bI)
	return uint32(bI)
}

// Tell GLS to delete this buffer
func (s *SSBO) Delete(gs *GLS) {
	gs.DeleteBuffers(s.bufferID)
}

//type PBO struct { // Pixel Buffer Object
// Make this implement the BufferObject interface
//}

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
func (b *BufferObjects) Values() iter.Seq[BufferObject] {
	return maps.Values(*b)
}

// Set sets a buffer object with its given id
func (b *BufferObjects) Set(bo BufferObject) {
	(*b)[bo.BufferID()] = bo
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
			if ok1 != ok2 {
				return false
			}
			// reaching this line implies that both are ok
			// otherwise, the map would be seriously broken
			if v1.BufferID() != v2.BufferID() {
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
func (b *BufferObjects) Bind(gs *GLS) error {
	var _errors error
	for _, bufferObject := range map[uint32]BufferObject(*b) {
		var err error = bufferObject.Bind(gs)
		_errors = errors.Join(_errors, err)
	}
	return _errors
}

// Calls Process for all buffer objects
func (b *BufferObjects) Process(gs *GLS, deltaTime time.Duration) error {
	var _errors error
	for _, bufferObject := range map[uint32]BufferObject(*b) {
		var err error = bufferObject.Process(gs, deltaTime)
		_errors = errors.Join(_errors, err)
		//TODO test if making this multithreaded is allowed & beneficial
	}
	return _errors
}

// Deletes all buffer objects from gls and removes those from the
// map
func (b *BufferObjects) DeleteBufferObjects(gs *GLS) {
	for id, bufferObject := range map[uint32]BufferObject(*b) {
		bufferObject.Delete(gs)
		(*b).Unset(id)
	}
}
