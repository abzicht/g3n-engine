// Copyright 2016 The G3N Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package graphic

import (
	"github.com/g3n/engine/core"
	"github.com/g3n/engine/geometry"
	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/material"
	"github.com/g3n/engine/math32"
)

// ParticleSim represents a geometry containing only particles
type ParticleSim struct {
	Graphic             // Embedded graphic
	uniMm   gls.Uniform // Model matrix uniform location cache
	uniMVm  gls.Uniform // Model view matrix uniform location cache
	uniMVPm gls.Uniform // Model view projection matrix uniform location cache
	uniNm   gls.Uniform // Normal matrix uniform cache
}

// NewParticleSim creates and returns a graphic particle sim object with the specified
// geometry and material.
func NewParticleSim(igeom *geometry.ParticleGeometry, imat material.IMaterial) *ParticleSim {

	p := new(ParticleSim)
	p.Graphic.Init(p, igeom, gls.POINTS)
	if imat != nil {
		p.AddMaterial(p, imat, 0, 0)
	}
	p.uniMm.Init("MM")    // ModelMatrix
	p.uniMVPm.Init("MVP") // ModelProjectionMatrix
	p.uniMVm.Init("MV")   // ModelViewMatrix
	p.uniNm.Init("NM")    // NormalMatrix
	return p
}

// RenderSetup is called by the engine before rendering this graphic.
func (p *ParticleSim) RenderSetup(gs *gls.GLS, rinfo *core.RenderInfo) {

	// Transfer uniform for model matrix
	mm := p.ModelMatrix()
	location := p.uniMm.Location(gs)
	gs.UniformMatrix4fv(location, 1, false, &mm[0])

	// Transfer model view projection matrix uniform
	mvpm := p.ModelViewProjectionMatrix()
	location = p.uniMVPm.Location(gs)
	gs.UniformMatrix4fv(location, 1, false, &mvpm[0])

	// Transfer model view matrix uniform
	mvm := p.ModelViewMatrix()
	location = p.uniMVm.Location(gs)
	gs.UniformMatrix4fv(location, 1, false, &mvm[0])

	// Calculates normal matrix and transfer uniform
	var nm math32.Matrix3
	nm.GetNormalMatrix(mvm)
	location = p.uniNm.Location(gs)
	gs.UniformMatrix3fv(location, 1, false, &nm[0])
}
