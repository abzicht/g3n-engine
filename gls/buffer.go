package gls

import (
	"fmt"
	"unsafe"
)

// BufferRaw points to raw data in user space, reachable by the CPU. It is typically
// created inside of buffer object callbacks
// and serves as the interface for communicating with
// compute shaders (or any other shader with access to shared buffers).
// BufferRaw makes no assumption on the buffer's data structure. If a user is
// as certain as it can possibly be, it is advised to convert BufferRaw into a
// BufferTyped instance that offers direct buffer modifications for nearly all
// basic GLS datatypes.
type BufferRaw struct {
	Address unsafe.Pointer
	Size    uint32
}

// Create a new BufferRaw that points to address p with a given size
// Needless to say, using this is 'unsafe'
func NewBufferRaw(p unsafe.Pointer, size uint32) *BufferRaw {
	b := new(BufferRaw)
	b.Init(p, size)
	return b
}

func (b *BufferRaw) Init(p unsafe.Pointer, size uint32) {
	b.Address = p
	b.Size = size
}

// Convert a raw buffer to BufferTyped
func (b *BufferRaw) Typed() *BufferTyped {
	return NewBufferTyped(b.Address, b.Size)
}

// Create a new BufferRaw whose address is the sum of the parent buffer's
// address and the given address. Note: the buffer on that the function
// is being called remains unchanged.
// Returns a new buffer that applies the given offset or an error, iff the
// otherwise returned buffer would point outside of the parent's buffer area.
func (b *BufferRaw) Skip(offset uint32) (*BufferRaw, error) {
	if offset > b.Size {
		return nil, fmt.Errorf("Buffer overflow: Attempted to skip more bytes (%d) than there are in the buffer (size: %d)", offset, b.Size)
	}
	return NewBufferRaw(unsafe.Add(b.Address, offset), b.Size-offset), nil
}

// Create a new BufferRaw with the given size and an address that is at a
// given offset to the parent's buffer address.
// Returns a new buffer that applies the given offset and size or an error, iff the
// otherwise returned buffer would point outside of the parent's buffer area.
func (b *BufferRaw) Child(offset uint32, size uint32) (*BufferRaw, error) {
	if size+offset > b.Size {
		return nil, fmt.Errorf("Buffer overflow: Attempted to create a child buffer whose address space (offset: %d, size: %d) would be out of bounds of the parent buffer (size: %d)", offset, size, b.Size)
	}
	return NewBufferRaw(unsafe.Add(b.Address, offset), size), nil
}

// Return a slice of bytes with the specified length that starts at the
// index-th byte of the buffer.
func (b *BufferRaw) GetBytes(index uint32, length uint32) []byte {
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
func (b *BufferRaw) SetBytes(index uint32, data []byte) error {
	if index+uint32(len(data)) > b.Size {
		// Trying to write beyond the buffer? Come on!
		return fmt.Errorf("Buffer overflow: Attempted to write %d bytes to buffer at index %d, but only %d bytes are left", len(data), index, b.Size-index)
	}
	copy(unsafe.Slice((*byte)(unsafe.Add(b.Address, index)), len(data)), data)
	return nil
}

// Return the buffer as a slice of bytes.
func (b *BufferRaw) AsBytes() []byte {
	return unsafe.Slice((*byte)(b.Address), b.Size)
}
