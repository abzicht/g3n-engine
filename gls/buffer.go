package gls

import (
	"fmt"
	"iter"
	"unsafe"

	"github.com/g3n/engine/math32"
)

// BufferRAM points to data in user space, reachable by the CPU. It is typically
// created from GLS and serves as the interface for communicating with
// compute shaders.
type BufferRAM struct {
	Address unsafe.Pointer
	Size    uint32
}

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
		return fmt.Errorf("Buffer overflow prevented: Attempted to write %d bytes to buffer at index %d, but only %d bytes are left", len(data), index, b.Size-index)
	}
	copy(unsafe.Slice((*byte)(unsafe.Add(b.Address, index)), len(data)), data)
	return nil
}

// Return the buffer as a slice of bytes.
func (b *BufferRAM) AsBytes() []byte {
	return unsafe.Slice((*byte)(b.Address), b.Size)
}

// Return the typeSize bytes of the index-th element of a structured buffer
// where all elements are of the same size.
func (b *BufferRAM) get(index uint32, typeSize TypeSize) ([]byte, error) {
	var data []byte = b.GetBytes(index*uint32(typeSize), uint32(typeSize))
	if data == nil {
		err := fmt.Errorf("Failed to obtain data of size %d from buffer at index %d", typeSize, index)
		return nil, err
	}
	return data, nil
}

// Set the index-th Vector2. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferRAM) SetVector2(index uint32, vector *math32.Vector2) error {
	if index*uint32(SizeVec2Std430) > b.Size {
		return fmt.Errorf("Buffer overflow prevented: Attempted to write Vector2 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeVec2Std430))
	*(*float32)(p) = vector.X
	*(*float32)(unsafe.Add(p, 1*SizeFloatStd430)) = vector.Y
	return nil
}

// Return the index-th Vector2. This assumes that the buffer is an array of
// Vector2s.
func (b *BufferRAM) GetVector2(index uint32) (*math32.Vector2, error) {
	data, err := b.get(index, SizeVec2Std430)
	if err != nil {
		return nil, err
	}
	var vector *math32.Vector2 = math32.NewVec2()
	vector.X = *(*float32)(unsafe.Pointer(&data[0]))
	vector.Y = *(*float32)(unsafe.Pointer(&data[1*SizeFloatStd430]))
	return vector, nil
}

// Return the buffer as a Vector2 iterator. This assumes that the buffer is an array of
// Vector2s.
func (b *BufferRAM) AsVector2() iter.Seq2[uint32, math32.Vector2] {
	return func(yield func(uint32, math32.Vector2) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math32.Vector2
			v.X = *(*float32)(unsafe.Pointer(&_raw[i]))
			v.Y = *(*float32)(unsafe.Pointer(&_raw[i+1*uint32(SizeFloatStd430)]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += uint32(SizeVec2Std430)
		}
	}
}

// Set the index-th Vector3. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferRAM) SetVector3(index uint32, vector *math32.Vector3) error {
	if index*uint32(SizeVec3Std430) > b.Size {
		return fmt.Errorf("Buffer overflow prevented: Attempted to write Vector3 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeVec3Std430))
	*(*float32)(p) = vector.X
	*(*float32)(unsafe.Add(p, 1*SizeFloatStd430)) = vector.Y
	*(*float32)(unsafe.Add(p, 2*SizeFloatStd430)) = vector.Z
	return nil
}

// Return the index-th Vector3. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferRAM) GetVector3(index uint32) (*math32.Vector3, error) {
	data, err := b.get(index, SizeVec3Std430)
	if err != nil {
		return nil, err
	}
	var vector *math32.Vector3 = math32.NewVec3()
	vector.X = *(*float32)(unsafe.Pointer(&data[0]))
	vector.Y = *(*float32)(unsafe.Pointer(&data[1*SizeFloatStd430]))
	vector.Z = *(*float32)(unsafe.Pointer(&data[2*SizeFloatStd430]))
	return vector, nil
}

// Return the buffer as a Vector3 iterator. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferRAM) AsVector3() iter.Seq2[uint32, math32.Vector3] {
	return func(yield func(uint32, math32.Vector3) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math32.Vector3
			v.X = *(*float32)(unsafe.Pointer(&_raw[i]))
			v.Y = *(*float32)(unsafe.Pointer(&_raw[i+1*uint32(SizeFloatStd430)]))
			v.Z = *(*float32)(unsafe.Pointer(&_raw[i+2*uint32(SizeFloatStd430)]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += uint32(SizeVec3Std430)
		}
	}
}

// Set the index-th Vector4. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferRAM) SetVector4(index uint32, vector *math32.Vector4) error {
	if index*uint32(SizeVec4Std430) > b.Size {
		return fmt.Errorf("Buffer overflow prevented: Attempted to write Vector4 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeVec4Std430))
	*(*float32)(p) = vector.X
	*(*float32)(unsafe.Add(p, 1*SizeFloatStd430)) = vector.Y
	*(*float32)(unsafe.Add(p, 2*SizeFloatStd430)) = vector.Z
	*(*float32)(unsafe.Add(p, 3*SizeFloatStd430)) = vector.W
	return nil
}

// Return the index-th Vector4. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferRAM) GetVector4(index uint32) (*math32.Vector4, error) {
	data, err := b.get(index, SizeVec4Std430)
	if err != nil {
		return nil, err
	}
	var vector *math32.Vector4 = math32.NewVec4()
	vector.X = *(*float32)(unsafe.Pointer(&data[0]))
	vector.Y = *(*float32)(unsafe.Pointer(&data[1*SizeFloatStd430]))
	vector.Z = *(*float32)(unsafe.Pointer(&data[2*SizeFloatStd430]))
	vector.W = *(*float32)(unsafe.Pointer(&data[3*SizeFloatStd430]))
	return vector, nil
}

// Return the buffer as a Vector4 iterator. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferRAM) AsVector4() iter.Seq2[uint32, math32.Vector4] {
	return func(yield func(uint32, math32.Vector4) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math32.Vector4
			v.X = *(*float32)(unsafe.Pointer(&_raw[i]))
			v.Y = *(*float32)(unsafe.Pointer(&_raw[i+1*uint32(SizeFloatStd430)]))
			v.Z = *(*float32)(unsafe.Pointer(&_raw[i+2*uint32(SizeFloatStd430)]))
			v.W = *(*float32)(unsafe.Pointer(&_raw[i+3*uint32(SizeFloatStd430)]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += uint32(SizeVec4Std430)
		}
	}
}
