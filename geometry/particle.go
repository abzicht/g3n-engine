// Copyright 2016 The G3N Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package geometry

import (
	"math/rand/v2"

	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/math32"
)

type ParticleGeometry struct {
	Geometry
	numParticles uint32
	computeSpecs *gls.ComputeSpecs
}

func newParticleGeometry(numParticles uint32) *ParticleGeometry {
	p := new(ParticleGeometry)
	p.Geometry.Init()
	p.numParticles = numParticles
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
	return p
}

// Return the compute specs of this geometry
func (p *ParticleGeometry) ComputeSpecs() *gls.ComputeSpecs {
	return p.computeSpecs
}

// NewParticles creates a particle geometry with the specified number of
// particles using the specified compute program.
func NewParticles(numParticles uint32, width, height, length float32) *ParticleGeometry {
	// Validate arguments
	if min(width, height, length) <= 0 {
		panic("Invalid argument(s). Dimension must be greater than zero.")
	}

	particleGeom := newParticleGeometry(numParticles)
	// Create buffers
	particles := math32.NewArrayF32(int(numParticles), int(numParticles))
	for i, _ := range particles {
		particles[i] = rand.Float32()
	}
	particleGeom.SetIndices(math32.NewArrayU32(0, 0))
	particleGeom.AddVBO(gls.NewVBO(particles).AddAttrib(gls.VertexPosition))
	//.AddAtrib(gls.VertexColor)

	{
		// Boring stuff concerning the boundaries of the particle sim

		wHalf := width / 2
		hHalf := height / 2
		lHalf := length / 2
		// Update bounding particleGeom
		particleGeom.boundingBox.Min = math32.Vector3{X: -wHalf, Y: -hHalf, Z: -lHalf}
		particleGeom.boundingBox.Max = math32.Vector3{X: wHalf, Y: hHalf, Z: lHalf}
		particleGeom.boundingBoxValid = true
		// Update bounding sphere
		particleGeom.boundingSphere.Radius = math32.Sqrt(math32.Pow(width/2, 2) + math32.Pow(height/2, 2) + math32.Pow(length/2, 2))
		particleGeom.boundingSphereValid = true

		// Update area
		particleGeom.area = 2*width + 2*height + 2*length
		particleGeom.areaValid = true

		// Update volume
		particleGeom.volume = width * height * length
		particleGeom.volumeValid = true
	}

	return particleGeom
}
