package gls

import (
	"errors"
	"fmt"
	"iter"
	"maps"
	"time"
	"unsafe"

	"github.com/g3n/engine/math32"
)

type BufferObjects map[uint32]BufferObject

type BufferObject interface {
	// Returns the id that gls uses to identify this buffer
	GetBufferID() uint32
	// Binds this buffer to the provided gls
	Bind(gs *GLS)
	// Process the data held in buffer locally
	Process(gs *GLS, deltaTime time.Duration) error
	// Deletes this buffer from the provided gls
	Delete(gs *GLS)
}

// Shader Storage Buffer Object (SSBO) can be shared between CPU and compute
// shaders as well as between compute shaders and other types of shaders.
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
	Usage        UsageType
	Access       AccessType
	SSBOCallback SSBOCallback
	// Data type found in the buffer
	Size        uint32
	initialData []byte
}

// SSBOCallback is called within SSBO.Process and receives a BufferRAM object.
// This function must finish reading / writing to the buffer before it returns,
// otherwise, the shader won't take note of further updates to the buffer
// Note to end user: make good use of closures and use the correct AccessType!
type SSBOCallback func(b *BufferRAM, deltaTime time.Duration)

// BufferRAM points to data in user space, reachable by the CPU. It is typically
// created from GLS and serves as the interface for communicating with
// compute shaders.
type BufferRAM struct {
	Address unsafe.Pointer
	Size    uint32
}

// NumWorkGroups tell GLS how compute shaders should be processed
type NumWorkGroups struct {
	X uint32 // number of work groups in x axis
	Y uint32 // number of work groups in y axis
	Z uint32 // number of work groups in z axis
}

// Let's typify some constants so that users can't pass us the wrong ones. (If
// everything was uint32, who tells us that a GL constant's category fits the
// use case?)
type AccessType uint32
type UsageType uint32

// Usage Type with that glBufferData is called by Buffer Objects
const (
	BO_STREAM_DRAW  UsageType = STREAM_DRAW
	BO_STREAM_READ  UsageType = STREAM_READ
	BO_STREAM_COPY  UsageType = STREAM_COPY
	BO_STATIC_DRAW  UsageType = STATIC_DRAW
	BO_STATIC_READ  UsageType = STATIC_READ
	BO_STATIC_COPY  UsageType = STATIC_COPY
	BO_DYNAMIC_DRAW UsageType = DYNAMIC_DRAW
	BO_DYNAMIC_READ UsageType = DYNAMIC_READ
	BO_DYNAMIC_COPY UsageType = DYNAMIC_COPY
)

// Access Type with that glMapBuffer is called by Buffer Objects
const (
	// if using read only, changes made to the buffer by CPU are not reflected
	// to shaders
	BO_READ_ONLY  AccessType = READ_ONLY
	BO_WRITE_ONLY AccessType = WRITE_ONLY
	BO_READ_WRITE AccessType = READ_WRITE
)

// Create a new BufferRAM that points to address p with a given size
// Needless to say, using this is 'unsafe'
func NewBufferRAM(p unsafe.Pointer, size uint32) *BufferRAM {
	b := new(BufferRAM)
	b.Init(p, size)
	return b
}

func (b *BufferRAM) Init(p unsafe.Pointer, size uint32) {
	b.Address = p
	b.Size = size
}

// Return a slice of bytes with the specified length that starts at the
// index-th byte of the buffer.
func (b *BufferRAM) GetBytes(index uint32, length uint32) []byte {
	if index+length > b.Size {
		// Trying to read beyond the buffer? Come on!
		return nil
	}
	return unsafe.Slice((*byte)(unsafe.Add(b.Address, index)), length)
}

// Write a slice of bytes to the buffer, starting at the index-th position in
// the buffer.
// Returns an error when attempting to overflow the buffer (index + len(data) >
// b.Size)
func (b *BufferRAM) SetBytes(index uint32, data []byte) error {
	if index+uint32(len(data)) > b.Size {
		// Trying to write beyond the buffer? Come on!
		return fmt.Errorf("Buffer overflow prevented: Trying to write %d bytes to buffer at index %d, but only %d bytes are left", len(data), index, b.Size-index)
	}
	copy(unsafe.Slice((*byte)(unsafe.Add(b.Address, index)), len(data)), data)
	return nil
}

// Return the buffer as a slice of bytes.
func (b *BufferRAM) AsBytes() []byte {
	return unsafe.Slice((*byte)(b.Address), b.Size)
}

// Set the index-th Vector4. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferRAM) SetVector4(index uint32, vector *math32.Vector4) error {
	const float32size uint32 = uint32(unsafe.Sizeof(float32(0)))
	const vec4size uint32 = uint32(4 * float32size)
	if index*(vec4size+1) > b.Size {
		return fmt.Errorf("Buffer overflow prevented: Trying to write Vector4 (%d bytes) to buffer at index %d, but only %d bytes are left", vec4size, index*vec4size, b.Size-(index*vec4size))
	}

	p := unsafe.Add(b.Address, index*vec4size)
	*(*float32)(p) = vector.X
	*(*float32)(unsafe.Add(p, 1*float32size)) = vector.Y
	*(*float32)(unsafe.Add(p, 2*float32size)) = vector.Z
	*(*float32)(unsafe.Add(p, 3*float32size)) = vector.W
	return nil
}

// Return the index-th Vector4. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferRAM) GetVector4(index uint32) *math32.Vector4 {
	const float32size uint32 = uint32(unsafe.Sizeof(float32(0)))
	const vec4size uint32 = uint32(4 * float32size)
	var _bytes []byte = b.GetBytes(index*vec4size, vec4size)
	if _bytes == nil {
		return nil
	}
	var vector *math32.Vector4 = math32.NewVec4()
	vector.X = *(*float32)(unsafe.Pointer(&_bytes[0]))
	vector.Y = *(*float32)(unsafe.Pointer(&_bytes[1*float32size]))
	vector.Z = *(*float32)(unsafe.Pointer(&_bytes[2*float32size]))
	vector.W = *(*float32)(unsafe.Pointer(&_bytes[3*float32size]))
	return vector
}

// Return the buffer as a Vector4 iterator. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferRAM) AsVector4() iter.Seq2[uint32, math32.Vector4] {
	const float32size uint32 = uint32(unsafe.Sizeof(float32(0)))
	const vec4size uint32 = uint32(4 * float32size)
	return func(yield func(uint32, math32.Vector4) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math32.Vector4
			v.X = *(*float32)(unsafe.Pointer(&_raw[i+0*float32size]))
			v.Y = *(*float32)(unsafe.Pointer(&_raw[i+1*float32size]))
			v.Z = *(*float32)(unsafe.Pointer(&_raw[i+2*float32size]))
			v.W = *(*float32)(unsafe.Pointer(&_raw[i+3*float32size]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += vec4size
		}
	}
}

// Create a new SSBO of the given size that binds to a shader variable identified with bindingIndex
// The ssboCallback is called by (*SSBO).Process and receives the current
// buffer state. ssboCallback can apply changes on the buffer and reflect those
// to the shader, but only, if access is set to BO_WRITE_ONLY or
// BO_READ_WRITE.
// Use (*SSBO).SetInitialData to prefill the buffer before the first call to
// Process.
// Set usage to DYNAMIC_COPY / DYNAMIC_DRAW when expecting to modify this buffer's contents
func NewSSBO(gs *GLS, bindingIndex uint32, usage UsageType, access AccessType, ssboCallback SSBOCallback, size uint32) *SSBO {
	s := new(SSBO)
	s.Init(gs, bindingIndex, usage, access, ssboCallback, size)
	return s
}

// Initialize SSBO and generate a corresponding GLS buffer
func (s *SSBO) Init(gs *GLS, bindingIndex uint32, usage UsageType, access AccessType, ssboCallback SSBOCallback, size uint32) {
	s.BindingIndex = bindingIndex
	s.Usage = usage
	s.Access = access
	s.SSBOCallback = ssboCallback
	s.Size = size
	s.BufferID = gs.GenBuffer()
	s.initialData = nil
}

// Set the initial buffer data to the provided byte slice.
// This function is only effective when called before s.Bind() where the data
// is being applied. If provided data is larger than s.Size, the overshoot is
// being ignored
func (s *SSBO) SetInitialData(data []byte) {
	s.initialData = data
}

// Return the buffer id in GLS that this ssbo references
func (s *SSBO) GetBufferID() uint32 {
	return s.BufferID
}

// Binds this SSBO's GLS buffer to the provided GLS instance and copies the
// data to this buffer. If data is larger than s.Size, the rest is ignored
func (s *SSBO) Bind(gs *GLS) {
	gs.BindBuffer(SHADER_STORAGE_BUFFER, s.BufferID)
	gs.NamedBufferData(s.BufferID, s.Size, unsafe.Pointer(unsafe.SliceData(s.initialData)), uint32(s.Usage))
	gs.BindBufferBase(SHADER_STORAGE_BUFFER, s.BindingIndex, s.BufferID) // Bind to binding point found in shader
	gs.BindBuffer(SHADER_STORAGE_BUFFER, 0)                              // value 0 indicates: unbind!
	s.initialData = nil
}

// Load the GLS buffer into RAM and call the user-defined callback on that
// buffer before unbinding it.
func (s *SSBO) Process(gs *GLS, deltaTime time.Duration) error {
	gs.BindBuffer(SHADER_STORAGE_BUFFER, s.BufferID)
	ptr := gs.MapNamedBuffer(s.BufferID, int(s.Access))
	if ptr != uintptr(0) {
		s.SSBOCallback(NewBufferRAM(unsafe.Pointer(ptr), s.Size), deltaTime)
		gs.UnmapNamedBuffer(s.BufferID)
	} else {
		return fmt.Errorf("Failed to obtain SSBO buffer from GLS using glMapNamedBuffer for buffer with id %d", s.BufferID)
	}
	gs.BindBuffer(SHADER_STORAGE_BUFFER, 0) // unbind this buffer, clearing data
	return nil
}

// Tell GLS to delete this buffer
func (s *SSBO) Delete(gs *GLS) {
	gs.DeleteBuffers(s.BufferID)
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
			if (*b)[k].GetBufferID() != (*other)[k].GetBufferID() {
				return false
			}
			//v1, ok1 := (*b)[k]
			//v2, ok2 := (*other)[k]
			//if v1 != v2 || ok1 != ok2 {
			//	return false
			//}
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

func NewNumWorkGroups(x, y, z uint32) *NumWorkGroups {
	n := new(NumWorkGroups)
	n.X = x
	n.Y = y
	n.Z = z
	return n
}
