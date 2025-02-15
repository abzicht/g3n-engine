package gls

// NumWorkGroups tell GLS how compute shaders should be processed
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

// Let's typify some constants regarding buffer objects so that users can't pass the wrong ones. (If
// everything was uint32, who tells us that a GL constant's category fits the
// use case?)

type BOAccessType uint32
type BOUsageType uint32

// Usage Type with that glBufferData is called by Buffer Objects
const (
	BO_STREAM_DRAW  BOUsageType = STREAM_DRAW // do we need
	BO_STREAM_READ  BOUsageType = STREAM_READ // stream and
	BO_STREAM_COPY  BOUsageType = STREAM_COPY // static for
	BO_STATIC_DRAW  BOUsageType = STATIC_DRAW // our purposes?
	BO_STATIC_READ  BOUsageType = STATIC_READ
	BO_STATIC_COPY  BOUsageType = STATIC_COPY
	BO_DYNAMIC_DRAW BOUsageType = DYNAMIC_DRAW
	BO_DYNAMIC_READ BOUsageType = DYNAMIC_READ
	BO_DYNAMIC_COPY BOUsageType = DYNAMIC_COPY
)

// Access Type with that glMapBuffer is called by Buffer Objects
const (
	// Note: when using read only, changes made to the buffer by CPU are not reflected
	// to shaders
	BO_READ_ONLY  BOAccessType = READ_ONLY
	BO_WRITE_ONLY BOAccessType = WRITE_ONLY
	BO_READ_WRITE BOAccessType = READ_WRITE
)
