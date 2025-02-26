package gls

import (
	"fmt"
	"iter"
	"unsafe"
)

// Every line in this file is "unsafe" par excellence. It is better to look away.

/* BufferTyped can be created from BufferRaw when it was determined (by having
 * a look at it) that the underlying buffer is of the assumed type. Even then,
 * BufferTyped can't prevent you from hurting yourself. It assumes that all
 * bytes within [address,address+size] are of a given type (or of an array of that
 * type). When you know that this is not the case, e.g., because the buffer
 * is of mixed types or because type
 * consistency only starts at a certain offset from the buffer's address, then
 * you are advised to use Skip or Child to jump to the correct address or to
 * cast directly to a Go struct, as explained in the following.
 *
 * Instead of using the rich function set of BufferType, you can
 * also cast (raw) buffers to custom Go structs!
 * Consider this buffer in a std430 compute shader:
 *     layout(std430, binding = 0) buffer DataBuffer {
 *         uint i;
 *         vec3 loc;
 *         float speed;
 *         dvec4 data[];
 *     } D;
 * We can map this to the following Go struct:
 *     type DataBuffer struct {
 *         i     uint32
 *         _     [3]int32
 *         loc   math32.Vector3
 *         speed float32
 *         data  [5]math64.Vector4
 *     }
 * Using a raw / typed buffer b, this will cast correctly:
 * var d *DataBuffer3 = (*DataBuffer3)(b.Address)
 *
 * However, a lot can go wrong here: d.data must be a Go array, not a slice
 * (i.e., its length must be set)! Given that the buffer has a constant size,
 * this restriction is justified, as there is a way to determine that, e.g., the
 * length of d.data is 5.
 *
 * More importantly, we must apply correct padding. std430 has its way of
 * aligning structs and Go has its own way, too
 * (https://go101.org/article/memory-layout.html).
 * In the example above, we are forced to apply 12 byte of padding using the
 * underscore that is 3 times a 32 bit int: in GLS, uint has a size of 4 bytes
 * and vec3 wants to be packed into a 16 byte block, leaving 12 bytes in
 * between D.i and D.loc. Likewise, we need to consider the padding when
 * determining our targeted buffer size.
 * When being forced to pad, it is also a good time to rethink the struct
 * itself. In this example, putting loc at the first place would reduce the
 * padding to 8 bytes between d.speed and d.data.
 */
type BufferTyped struct {
	BufferRaw
}

// Create a new BufferTyped that points to address p with a given size
// Needless to say, using this is 'unsafe'
func NewBufferTyped(p unsafe.Pointer, size uint32) *BufferTyped {
	b := new(BufferTyped)
	b.BufferRaw.Init(p, size)
	return b
}

// Return the typeSize bytes of the index-th element of a structured buffer
// where all elements are of the same size.
func (b *BufferTyped) get(index uint32, typeSize TypeSize) ([]byte, error) {
	var data []byte = b.GetBytes(index*uint32(Strideof(typeSize)), uint32(typeSize))
	if data == nil {
		err := fmt.Errorf("Failed to obtain data of size %d from buffer at index %d", typeSize, index)
		return nil, err
	}
	return data, nil
}

// Map an index to the correct buffer address by accounting for strides.
func mapIndex[T BufferType](index uint32) uint32 {
	return uint32(StrideofT[T]()) * index
}

// Set a value t of type T within the given buffer. t is written to the
// index-th-element, assuming that elements of the buffer are of type T.
func Set[T BufferType](b *BufferTyped, index uint32, t T) error {
	offset := mapIndex[T](index)
	if offset > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write data of type %T to buffer at offset %d", t, offset)
	}
	p := unsafe.Add(b.Address, offset)
	*(*T)(p) = t
	return nil
}

// Return the index-th value of type T. This assumes that the buffer is an array of
// elements of type T.
func Get[T BufferType](b *BufferTyped, index uint32) (t T, err error) {
	data, err := b.get(index, SizeofT[T]())
	if err != nil {
		return
	}
	return *(*T)(unsafe.Pointer(&data[0])), nil
}

// Return the buffer as a typed iterator. This assumes that the buffer is an array of
// elements of type T.
func AsT[T BufferType](b *BufferTyped) iter.Seq2[uint32, T] {
	return func(yield func(uint32, T) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			t_ := *(*T)(unsafe.Pointer(&_raw[i]))
			if !yield(index, t_) {
				return
			}
			index += 1
			i += uint32(StrideofT[T]())
		}
	}
}

// Create a new buffer for the given slice, accounting for OpenGL-specific array
// strides
func AsBuffer[T BufferType](slice []T) *BufferTyped {
	if len(slice) == 0 {
		return nil
	}
	stride := uint32(Strideof(slice[0]))
	size := uint32(Sizeof(slice[0]))
	bufferSize := uint32(len(slice)) * stride
	if size == stride {
		// no need to do the heavy lifting, the buffer can point to the
		// existing slice
		return NewBufferTyped(unsafe.Pointer(unsafe.SliceData(slice)), bufferSize)
	}
	b := new(BufferTyped)
	buffer := make([]byte, bufferSize, bufferSize)
	for i := uint32(0); i < uint32(len(slice)); i++ {
		offset := i * stride
		sliceElemBuffer := NewBufferRaw(unsafe.Pointer(&slice[i]), size)
		if int(size) != copy(buffer[offset:], sliceElemBuffer.AsBytes()) {
			panic("Failed to copy bytes to buffer")
		}
	}

	b.BufferRaw.Init(unsafe.Pointer(unsafe.SliceData(buffer)), bufferSize)
	return b
}
