// Copyright 2016 The G3N Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package geometry

import (
	"fmt"
	"math/rand/v2"
	"unsafe"

	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/math32"
)

type ParticleGeometry struct {
	Geometry
	numParticles uint32
	dimensions   *math32.Vector3
	// Buffer object of the compute shader that holds the particle positions
	// as an vec3 array
	positions gls.BufferObject
}

//var particlesBufferSize uint32
//{
//	var particles_ [30]Particle
//	numParticles = uint32(len(particles_))
//	particlesBufferSize = uint32(unsafe.Sizeof(particles_))
//}
//callback := func(b_ *gls.BufferRaw, deltaTime time.Duration) {
//	//b := b_.Typed()
//	//var particles []Particle = (*[numParticles]Particle)(b_.Address)[:]
//	var particles []Particle = unsafe.Slice((*Particle)(b_.Address), numParticles)
//	for i, p := range particles {
//		fmt.Printf("part. %d (pos: %+v, vel: %+v); ", i, p.pos, p.velocity)
//	}
//}
//particlesBO := gls.NewSSBO(gs, 0,
//	gls.BO_DYNAMIC_COPY, gls.BO_READ_WRITE, callback,
//	particlesBufferSize) //.SetInitialBuffer()
//ssbos := gls.NewBufferObjects()
//ssbos.Set(particlesBO)
//p.computeSpecs = gls.NewComputeSpecs(computeProg, "4_3", *gls.NewShaderDefines(), ssbos)

// NewParticles creates a particle geometry with the specified number of
// particles whose position is controlled by the provided buffer that is
// expected to be an array of vec3s with length numParticles and that binds to
// binding index 0. If
// positions==nil, a random distribution of particles is applied (you should
// really provide a custom buffer to achieve meaningful effects).
func NewParticles(numParticles uint32, positions gls.BufferObject, dimensions *math32.Vector3) *ParticleGeometry {
	p := new(ParticleGeometry)
	p.Init(numParticles, positions, dimensions)
	return p
}
func (p *ParticleGeometry) Init(numParticles uint32, positions gls.BufferObject, dimensions *math32.Vector3) {
	p.Geometry.Init()
	p.SetBoundingBox(dimensions)
	p.numParticles = numParticles
	p.dimensions = dimensions
	// Create buffers
	p.positions = positions
	//.AddAtrib(gls.VertexColor)
}

func (p *ParticleGeometry) Items() int {
	return int(p.numParticles)
}
func (g *ParticleGeometry) Indices() math32.ArrayU32 {

	fmt.Println("Helloo")
	return g.indices
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
func (p *ParticleGeometry) RenderSetup(gs *gls.GLS) {
	// First time initialization
	if p.gs == nil {
		// Generate VAO
		p.handleVAO = gs.GenVertexArray()
		// Save pointer to gs indicating initialization was done
		p.gs = gs
		// User didn't set a buffer, let's prepare a random one
		if p.positions == nil {
			particles := math32.NewArrayF32(int(p.numParticles), int(p.numParticles))
			for i := 0; i < len(particles); i += 3 {
				particles[i] = (rand.Float32() - 0.5) * p.dimensions.X / 2
				particles[i+1] = (rand.Float32() - 0.5) * p.dimensions.Y / 2
				particles[i+2] = (rand.Float32() - 0.5) * p.dimensions.Z / 2
			}
			ssbo := gls.NewSSBO(p.gs, 0, gls.DYNAMIC_COPY, gls.BO_READ_WRITE, nil, uint32(unsafe.Sizeof(&particles)))
			ssbo.SetInitialBuffer(gls.NewBufferRaw(unsafe.Pointer(unsafe.SliceData(particles)), uint32(unsafe.Sizeof(&particles))))
			p.positions = ssbo
		}
	}

	// Update VBOs
	gs.BindVertexArray(p.handleVAO)
	for _, vbo := range p.vbos {
		vbo.Transfer(gs)
	}
	//gs.DrawArrays(gls.POINTS, 0, int32(p.numParticles))
}

// Set the positions buffer for the particles in this geometry
func (p *ParticleGeometry) SetPositionsBO(positions gls.BufferObject) {
	p.positions = positions
}
