// Copyright 2016 The G3N Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package geometry

import (
	"unsafe"

	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/math32"
)

const (
	ParticlePositionBinding = 0
)

type shapeDescriptor struct {
	gs    *gls.GLS
	shape *Geometry
}

func newShapeDescriptor() *shapeDescriptor {
	s := new(shapeDescriptor)
	return s
}

func (s *shapeDescriptor) RenderSetup(gs *gls.GLS) {
	if s.shape == nil {
		return
	} //nothing tbd
	if s.gs == nil {
		s.gs = gs
		if s.shape != nil { // prepare the buffer, thereafter forget the shape
			s.shape.handleIndices = gs.GenBuffer()
		}
		for _, vbo := range s.shape.vbos {
			vbo.Transfer(gs)
		}
	}
	for _, vbo := range s.shape.vbos {
		s.gs.BindBuffer(gls.ARRAY_BUFFER, vbo.Handle())
	}
	// Update Indices buffer if necessary
	if s.shape.indices.Size() > 0 && s.shape.updateIndices {
		gs.BindBuffer(gls.ELEMENT_ARRAY_BUFFER, s.shape.handleIndices)
		gs.BufferData(gls.ELEMENT_ARRAY_BUFFER, s.shape.indices.Bytes(), unsafe.Pointer(unsafe.SliceData(s.shape.indices.ToUint32())), gls.STATIC_DRAW)
		s.shape.updateIndices = false
	}
}

type ParticleGeometry struct {
	Geometry
	numParticles    uint32
	dimensions      *math32.Vector3
	positionsBuffer *gls.SSBO
	shapeDescriptor *shapeDescriptor
	uniIsInstanced  gls.Uniform
}

// NewParticles creates a particle geometry with the specified number of
// particles whose position is controlled by a buffer that is
// expected to be an array of vec3s with length numParticles and that binds to
// binding index 0.
func NewParticles(numParticles uint32, positionsBuffer *gls.SSBO, dimensions *math32.Vector3) *ParticleGeometry {
	p := new(ParticleGeometry)
	p.Init(numParticles, positionsBuffer, dimensions)
	return p
}
func (p *ParticleGeometry) Init(numParticles uint32, positionsBuffer *gls.SSBO, dimensions *math32.Vector3) {
	p.Geometry.Init()
	p.SetBoundingBox(dimensions)
	p.numParticles = numParticles
	p.dimensions = dimensions
	p.positionsBuffer = positionsBuffer
	p.shapeDescriptor = newShapeDescriptor()
	p.shapeDescriptor.shape = nil
	p.uniIsInstanced.Init("IsInstanced")
}

// Set the shape of individual particles
func (p *ParticleGeometry) SetParticleShape(shape *Geometry) {
	p.shapeDescriptor.shape = shape
}

func (p *ParticleGeometry) IsInstanced() bool {
	return p.shapeDescriptor.shape != nil
}

func (p *ParticleGeometry) Instance() *Geometry {
	return p.shapeDescriptor.shape
}

func (p *ParticleGeometry) Items() int {
	return int(p.numParticles)
}

// Set the bounding box dimensions for the particle geometry
func (p *ParticleGeometry) SetBoundingBox(dimensions *math32.Vector3) {
	width := dimensions.X
	height := dimensions.Y
	length := dimensions.Z
	// Validate arguments
	if min(width, height, length) <= 0 {
		panic("Invalid argument(s). Dimension must be greater than zero.")
	}
	// Stuff concerning the boundaries of the particle sim

	wHalf := width / 2
	hHalf := height / 2
	lHalf := length / 2
	// Update bounding particleGeom
	p.boundingBox.Min = math32.Vector3{X: -wHalf, Y: -hHalf, Z: -lHalf}
	p.boundingBox.Max = math32.Vector3{X: wHalf, Y: hHalf, Z: lHalf}
	p.boundingBoxValid = true
	// Update bounding sphere
	p.boundingSphere.Radius = math32.Sqrt(math32.Pow(width/2, 2) + math32.Pow(height/2, 2) + math32.Pow(length/2, 2))
	p.boundingSphereValid = true

	// Update area
	p.area = 2*width + 2*height + 2*length
	p.areaValid = true

	// Update volume
	p.volume = width * height * length
	p.volumeValid = true
}

// RenderSetup is called by the renderer before drawing the geometry.
// It links the particle positions from the compute shader with the vertex
// buffer object
func (p *ParticleGeometry) InactiveRenderSetup(gs *gls.GLS) {
	// First time initialization
	if p.gs == nil {
		// Generate VAO
		p.handleVAO = gs.GenVertexArray()
		// Save pointer to gs indicating initialization was done
		p.gs = gs
	}
	// Update VBOs
	p.gs.BindVertexArray(p.handleVAO)
	for _, vbo := range p.vbos {
		vbo.Transfer(gs)
	}

	p.shapeDescriptor.RenderSetup(gs)
}
func (p *ParticleGeometry) RenderSetup(gs *gls.GLS) {
	// First time initialization
	if p.gs == nil {
		p.gs = gs
		// Generate VAO
		p.handleVAO = gs.GenVertexArray()
		// Save pointer to gs indicating initialization was done
	}
	// Update VBOs
	p.gs.BindVertexArray(p.handleVAO)
	for _, vbo := range p.vbos {
		vbo.Transfer(gs)
	}
	if p.IsInstanced() {
		p.shapeDescriptor.RenderSetup(gs)
	}
	if p.positionsBuffer != nil {
		p.positionsBuffer.Bind(gs)
	}
	gs.Uniform1b(p.uniIsInstanced.Location(gs), p.IsInstanced())
}
