package gls

import (
	"fmt"
	"iter"
	"unsafe"

	"github.com/g3n/engine/math32"
	"github.com/g3n/engine/math64"
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
 *     layout(std430, shared, binding = 0) buffer DataBuffer {
 *         uint i;
 *         vec3 loc;
 *         float speed;
 *         dvec4 data[];
 *     } D;
 * We can map this to the following Go struct:
 *     type DataBuffer struct {
 *         i     uint32
 *         _     [3]atomic.Int32
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
	var data []byte = b.GetBytes(index*uint32(typeSize), uint32(typeSize))
	if data == nil {
		err := fmt.Errorf("Failed to obtain data of size %d from buffer at index %d", typeSize, index)
		return nil, err
	}
	return data, nil
}

// Set the index-th bool. This assumes that the buffer is an array of
// bools.
func (b *BufferTyped) SetBool(index uint32, b_ bool) error {
	if index*uint32(SizeBoolStd430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write bool to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeBoolStd430))
	if b_ {
		*(*int32)(p) = int32(1)
	} else {
		*(*int32)(p) = int32(0)
	}
	return nil
}

// Return the index-th bool. This assumes that the buffer is an array of
// bools.
func (b *BufferTyped) GetBool(index uint32) (bool, error) {
	data, err := b.get(index, SizeBoolStd430)
	if err != nil {
		return false, err
	}
	return *(*int32)(unsafe.Pointer(&data[0])) == 1, nil
}

// Return the buffer as a bool iterator. This assumes that the buffer is an array of
// bools.
func (b *BufferTyped) AsBool() iter.Seq2[uint32, bool] {
	return func(yield func(uint32, bool) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			b_ := *(*int32)(unsafe.Pointer(&_raw[i])) == 1
			if !yield(index, b_) {
				return
			}
			index += 1
			i += uint32(SizeBoolStd430)
		}
	}
}

// Set the index-th int32. This assumes that the buffer is an array of
// int32s.
func (b *BufferTyped) SetInt(index uint32, i int32) error {
	if index*uint32(SizeIntStd430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write int32 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeIntStd430))
	*(*int32)(p) = i
	return nil
}

// Return the index-th int32. This assumes that the buffer is an array of
// int32s.
func (b *BufferTyped) GetInt(index uint32) (int32, error) {
	data, err := b.get(index, SizeIntStd430)
	if err != nil {
		return 0, err
	}
	return *(*int32)(unsafe.Pointer(&data[0])), nil
}

// Return the buffer as a int32 iterator. This assumes that the buffer is an array of
// int32s.
func (b *BufferTyped) AsInt() iter.Seq2[uint32, int32] {
	return func(yield func(uint32, int32) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			integerVal := *(*int32)(unsafe.Pointer(&_raw[i]))
			if !yield(index, integerVal) {
				return
			}
			index += 1
			i += uint32(SizeIntStd430)
		}
	}
}

// Set the index-th uint32. This assumes that the buffer is an array of
// uint32s.
func (b *BufferTyped) SetUint(index uint32, i uint32) error {
	if index*uint32(SizeUintStd430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write uint32 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeUintStd430))
	*(*uint32)(p) = i
	return nil
}

// Return the index-th uint32. This assumes that the buffer is an array of
// uint32s.
func (b *BufferTyped) GetUint(index uint32) (uint32, error) {
	data, err := b.get(index, SizeUintStd430)
	if err != nil {
		return 0, err
	}
	return *(*uint32)(unsafe.Pointer(&data[0])), nil
}

// Return the buffer as a uint32 iterator. This assumes that the buffer is an array of
// uint32s.
func (b *BufferTyped) AsUint() iter.Seq2[uint32, uint32] {
	return func(yield func(uint32, uint32) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			f := *(*uint32)(unsafe.Pointer(&_raw[i]))
			if !yield(index, f) {
				return
			}
			index += 1
			i += uint32(SizeUintStd430)
		}
	}
}

// Set the index-th float32. This assumes that the buffer is an array of
// float32s.
func (b *BufferTyped) SetFloat(index uint32, f float32) error {
	if index*uint32(SizeFloatStd430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write float32 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeFloatStd430))
	*(*float32)(p) = f
	return nil
}

// Return the index-th float32. This assumes that the buffer is an array of
// float32s.
func (b *BufferTyped) GetFloat(index uint32) (float32, error) {
	data, err := b.get(index, SizeFloatStd430)
	if err != nil {
		return 0, err
	}
	return *(*float32)(unsafe.Pointer(&data[0])), nil
}

// Return the buffer as a float32 iterator. This assumes that the buffer is an array of
// float32s.
func (b *BufferTyped) AsFloat() iter.Seq2[uint32, float32] {
	return func(yield func(uint32, float32) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			f := *(*float32)(unsafe.Pointer(&_raw[i]))
			if !yield(index, f) {
				return
			}
			index += 1
			i += uint32(SizeFloatStd430)
		}
	}
}

// Set the index-th float64. This assumes that the buffer is an array of
// float64s.
func (b *BufferTyped) SetDouble(index uint32, f float64) error {
	if index*uint32(SizeDoubleStd430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write float64 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeDoubleStd430))
	*(*float64)(p) = f
	return nil
}

// Return the index-th float64. This assumes that the buffer is an array of
// float64s.
func (b *BufferTyped) GetDouble(index uint32) (float64, error) {
	data, err := b.get(index, SizeDoubleStd430)
	if err != nil {
		return 0, err
	}
	return *(*float64)(unsafe.Pointer(&data[0])), nil
}

// Return the buffer as a float64 iterator. This assumes that the buffer is an array of
// float64s.
func (b *BufferTyped) AsDouble() iter.Seq2[uint32, float64] {
	return func(yield func(uint32, float64) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			f := *(*float64)(unsafe.Pointer(&_raw[i]))
			if !yield(index, f) {
				return
			}
			index += 1
			i += uint32(SizeDoubleStd430)
		}
	}
}

// Set the index-th Vector2. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferTyped) SetVec2(index uint32, vector *math32.Vector2) error {
	if index*uint32(SizeVec2Std430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write Vector2 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeVec2Std430))
	*(*float32)(p) = vector.X
	*(*float32)(unsafe.Add(p, 1*SizeFloatStd430)) = vector.Y
	return nil
}

// Return the index-th Vector2. This assumes that the buffer is an array of
// Vector2s.
func (b *BufferTyped) GetVec2(index uint32) (*math32.Vector2, error) {
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
func (b *BufferTyped) AsVec2() iter.Seq2[uint32, math32.Vector2] {
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
func (b *BufferTyped) SetVec3(index uint32, vector *math32.Vector3) error {
	if index*uint32(SizeVec3Std430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write Vector3 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeVec3Std430))
	*(*float32)(p) = vector.X
	*(*float32)(unsafe.Add(p, 1*SizeFloatStd430)) = vector.Y
	*(*float32)(unsafe.Add(p, 2*SizeFloatStd430)) = vector.Z
	return nil
}

// Return the index-th Vector3. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferTyped) GetVec3(index uint32) (*math32.Vector3, error) {
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
func (b *BufferTyped) AsVec3() iter.Seq2[uint32, math32.Vector3] {
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
func (b *BufferTyped) SetVec4(index uint32, vector *math32.Vector4) error {
	if index*uint32(SizeVec4Std430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write Vector4 to buffer at index %d", index)
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
func (b *BufferTyped) GetVec4(index uint32) (*math32.Vector4, error) {
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
func (b *BufferTyped) AsVec4() iter.Seq2[uint32, math32.Vector4] {
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

// Set the index-th Vector2. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferTyped) SetDvec2(index uint32, vector *math64.Vector2) error {
	if index*uint32(SizeDvec2Std430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write Vector2 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeDvec2Std430))
	*(*float64)(p) = vector.X
	*(*float64)(unsafe.Add(p, 1*SizeDoubleStd430)) = vector.Y
	return nil
}

// Return the index-th Vector2. This assumes that the buffer is an array of
// Vector2s.
func (b *BufferTyped) GetDvec2(index uint32) (*math64.Vector2, error) {
	data, err := b.get(index, SizeDvec2Std430)
	if err != nil {
		return nil, err
	}
	var vector *math64.Vector2 = math64.NewVec2()
	vector.X = *(*float64)(unsafe.Pointer(&data[0]))
	vector.Y = *(*float64)(unsafe.Pointer(&data[1*SizeDoubleStd430]))
	return vector, nil
}

// Return the buffer as a Vector2 iterator. This assumes that the buffer is an array of
// Vector2s.
func (b *BufferTyped) AsDvec2() iter.Seq2[uint32, math64.Vector2] {
	return func(yield func(uint32, math64.Vector2) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math64.Vector2
			v.X = *(*float64)(unsafe.Pointer(&_raw[i]))
			v.Y = *(*float64)(unsafe.Pointer(&_raw[i+1*uint32(SizeDoubleStd430)]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += uint32(SizeDvec2Std430)
		}
	}
}

// Set the index-th Vector3. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferTyped) SetDvec3(index uint32, vector *math64.Vector3) error {
	if index*uint32(SizeDvec3Std430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write Vector3 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeDvec3Std430))
	*(*float64)(p) = vector.X
	*(*float64)(unsafe.Add(p, 1*SizeDoubleStd430)) = vector.Y
	*(*float64)(unsafe.Add(p, 2*SizeDoubleStd430)) = vector.Z
	return nil
}

// Return the index-th Vector3. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferTyped) GetDvec3(index uint32) (*math64.Vector3, error) {
	data, err := b.get(index, SizeDvec3Std430)
	if err != nil {
		return nil, err
	}
	var vector *math64.Vector3 = math64.NewVec3()
	vector.X = *(*float64)(unsafe.Pointer(&data[0]))
	vector.Y = *(*float64)(unsafe.Pointer(&data[1*SizeDoubleStd430]))
	vector.Z = *(*float64)(unsafe.Pointer(&data[2*SizeDoubleStd430]))
	return vector, nil
}

// Return the buffer as a Vector3 iterator. This assumes that the buffer is an array of
// Vector3s.
func (b *BufferTyped) AsDvec3() iter.Seq2[uint32, math64.Vector3] {
	return func(yield func(uint32, math64.Vector3) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math64.Vector3
			v.X = *(*float64)(unsafe.Pointer(&_raw[i]))
			v.Y = *(*float64)(unsafe.Pointer(&_raw[i+1*uint32(SizeDoubleStd430)]))
			v.Z = *(*float64)(unsafe.Pointer(&_raw[i+2*uint32(SizeDoubleStd430)]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += uint32(SizeDvec3Std430)
		}
	}
}

// Set the index-th Vector4. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferTyped) SetDvec4(index uint32, vector *math64.Vector4) error {
	if index*uint32(SizeDvec4Std430) > b.Size {
		return fmt.Errorf("Buffer overflow: Attempted to write Vector4 to buffer at index %d", index)
	}

	p := unsafe.Add(b.Address, index*uint32(SizeDvec4Std430))
	*(*float64)(p) = vector.X
	*(*float64)(unsafe.Add(p, 1*SizeDoubleStd430)) = vector.Y
	*(*float64)(unsafe.Add(p, 2*SizeDoubleStd430)) = vector.Z
	*(*float64)(unsafe.Add(p, 3*SizeDoubleStd430)) = vector.W
	return nil
}

// Return the index-th Vector4. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferTyped) GetDvec4(index uint32) (*math64.Vector4, error) {
	data, err := b.get(index, SizeDvec4Std430)
	if err != nil {
		return nil, err
	}
	var vector *math64.Vector4 = math64.NewVec4()
	vector.X = *(*float64)(unsafe.Pointer(&data[0]))
	vector.Y = *(*float64)(unsafe.Pointer(&data[1*SizeDoubleStd430]))
	vector.Z = *(*float64)(unsafe.Pointer(&data[2*SizeDoubleStd430]))
	vector.W = *(*float64)(unsafe.Pointer(&data[3*SizeDoubleStd430]))
	return vector, nil
}

// Return the buffer as a Vector4 iterator. This assumes that the buffer is an array of
// Vector4s.
func (b *BufferTyped) AsDvec4() iter.Seq2[uint32, math64.Vector4] {
	return func(yield func(uint32, math64.Vector4) bool) {
		_raw := b.AsBytes()
		var i, index uint32 = 0, 0
		for i < uint32(len(_raw)) {
			var v math64.Vector4
			v.X = *(*float64)(unsafe.Pointer(&_raw[i]))
			v.Y = *(*float64)(unsafe.Pointer(&_raw[i+1*uint32(SizeDoubleStd430)]))
			v.Z = *(*float64)(unsafe.Pointer(&_raw[i+2*uint32(SizeDoubleStd430)]))
			v.W = *(*float64)(unsafe.Pointer(&_raw[i+3*uint32(SizeDoubleStd430)]))
			if !yield(index, v) {
				return
			}
			index += 1
			i += uint32(SizeDvec4Std430)
		}
	}
}
