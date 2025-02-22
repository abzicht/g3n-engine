// Copyright 2016 The G3N Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package graphic

import (
	"github.com/g3n/engine/core"
	"github.com/g3n/engine/geometry"
	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/material"
)

// ParticleSim represents a geometry containing only particles
type ParticleSim struct {
	Graphic             // Embedded graphic
	uniMVPm gls.Uniform // Model view projection matrix uniform location cache
	uniMVm  gls.Uniform // Model view matrix uniform location cache
}

// NewParticleSim creates and returns a graphic particle sim object with the specified
// geometry and material.
func NewParticleSim(igeom *geometry.ParticleGeometry, imat material.IMaterial) *ParticleSim {

	p := new(ParticleSim)
	p.Graphic.Init(p, igeom, gls.POINTS)
	if imat != nil {
		p.AddMaterial(p, imat, 0, 0)
	}
	p.uniMVPm.Init("MVP")
	p.uniMVm.Init("MV")
	return p
}

// RenderSetup is called by the engine before rendering this graphic.
func (p *ParticleSim) RenderSetup(gs *gls.GLS, rinfo *core.RenderInfo) {

	// Transfer model view projection matrix uniform
	mvpm := p.ModelViewProjectionMatrix()
	location := p.uniMVPm.Location(gs)
	gs.UniformMatrix4fv(location, 1, false, &mvpm[0])

	// Transfer model view matrix uniform
	mvm := p.ModelViewMatrix()
	location = p.uniMVm.Location(gs)
	gs.UniformMatrix4fv(location, 1, false, &mvm[0])
}
