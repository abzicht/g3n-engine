package gls

import (
	"unsafe"

	"github.com/g3n/engine/math32"
	"github.com/g3n/engine/math64"
)

// Returns the size, in bytes, of math32 and math64 vectors, matrices, and
// primitive types of Go.
func Sizeof(v any) TypeSize {
	switch v.(type) {
	case math32.Vector2:
		return SizeVec2Std430
	case math32.Vector3:
		return SizeVec3Std430
	case math32.Vector4:
		return SizeVec4Std430
	case math32.Matrix3:
		return SizeMat3Std430
	case math32.Matrix4:
		return SizeMat4Std430

	case math64.Vector2:
		return SizeDvec2Std430
	case math64.Vector3:
		return SizeDvec3Std430
	case math64.Vector4:
		return SizeDvec4Std430
	default:
		// Caution: just because there is a default doesn't mean that it can
		// handle all types!
		// What it can handle: (u)int(32/64), bool, float(32/64)
		return TypeSize(unsafe.Sizeof(v))
	}
}

type BufferType interface {
	bool | int32 | uint32 | float32 | float64 | math32.Vector2 | math32.Vector3 | math32.Vector4 | math32.Matrix3 | math32.Matrix4 | math64.Vector2 | math64.Vector3 | math64.Vector4
}

func GetTypeSize[T BufferType]() TypeSize {
	var t T
	switch any(t).(type) {
	case bool:
		return SizeBoolStd430
	case int32:
		return SizeBoolStd430
	case uint32:
		return SizeBoolStd430
	case float32:
		return SizeBoolStd430
	case float64:
		return SizeBoolStd430
	case math32.Vector2:
		return SizeVec2Std430
	case math32.Vector3:
		return SizeVec3Std430
	case math32.Vector4:
		return SizeVec4Std430
	case math32.Matrix3:
		return SizeMat3Std430
	case math32.Matrix4:
		return SizeMat4Std430
	case math64.Vector2:
		return SizeDvec2Std430
	case math64.Vector3:
		return SizeDvec3Std430
	case math64.Vector4:
		return SizeDvec4Std430
	}
	return TypeSize(0)
}

// Size, in bytes, of (GLSL specific) data types. This follows the naming of
// https://www.khronos.org/opengl/wiki/Data_Type_(GLSL), and not of Go/G3N
type TypeSize byte

const (
	// For now, we only support types of GLSL std430
	// Primitives
	// Boolean
	SizeBoolStd430 = TypeSize(unsafe.Sizeof(bool(false)))
	// Integer
	SizeIntStd430 = TypeSize(unsafe.Sizeof(int32(0)))
	// Unsigned integer
	SizeUintStd430 = TypeSize(unsafe.Sizeof(uint32(0)))
	// Single Precision
	SizeFloatStd430 = TypeSize(unsafe.Sizeof(float32(0)))
	// Double Precision
	SizeDoubleStd430 = TypeSize(unsafe.Sizeof(float64(0)))
	// Boolean Vectors
	SizeBvec2Std430 = TypeSize(2 * SizeBoolStd430)
	SizeBvec3Std430 = TypeSize(3 * SizeBoolStd430)
	SizeBvec4Std430 = TypeSize(4 * SizeBoolStd430)
	// Integer vectors
	SizeIvec2Std430 = TypeSize(2 * SizeIntStd430)
	SizeIvec3Std430 = TypeSize(3 * SizeIntStd430)
	SizeIvec4Std430 = TypeSize(4 * SizeIntStd430)
	// Unsigned integer vectors
	SizeUvec2Std430 = TypeSize(2 * SizeUintStd430)
	SizeUvec3Std430 = TypeSize(3 * SizeUintStd430)
	SizeUvec4Std430 = TypeSize(4 * SizeUintStd430)
	// Single precision vectors
	SizeVec2Std430 = TypeSize(2 * SizeFloatStd430)
	SizeVec3Std430 = TypeSize(3 * SizeFloatStd430)
	SizeVec4Std430 = TypeSize(4 * SizeFloatStd430)
	// Double precision vectors
	SizeDvec2Std430 = TypeSize(2 * SizeDoubleStd430)
	SizeDvec3Std430 = TypeSize(3 * SizeDoubleStd430)
	SizeDvec4Std430 = TypeSize(4 * SizeDoubleStd430)
	// Matrices
	SizeMat3Std430   = TypeSize(3 * 3 * SizeFloatStd430)
	SizeMat2x3Std430 = TypeSize(2 * 3 * SizeFloatStd430)
	SizeMat3x2Std430 = TypeSize(3 * 2 * SizeFloatStd430)
	SizeMat4Std430   = TypeSize(4 * 4 * SizeFloatStd430)
	SizeMat2x4Std430 = TypeSize(2 * 4 * SizeFloatStd430)
	SizeMat3x4Std430 = TypeSize(3 * 4 * SizeFloatStd430)
	SizeMat4x2Std430 = TypeSize(4 * 2 * SizeFloatStd430)
	SizeMat4x3Std430 = TypeSize(4 * 3 * SizeFloatStd430)
)
