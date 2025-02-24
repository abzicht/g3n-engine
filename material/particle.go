package material

import (
	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/math32"
)

const (
	ParticleColorBinding = 1
)

type ParticleMaterial struct {
	Standard    // Embedded standard material
	customColor bool
}

// Create a new particle material with the given color and the shader program
// "particle". Use SetShader to use a custom particle shader program.
// Set useColorSSBO to tell the shader to load custom color data from a SSBO
// instead of rendering the given material
func NewParticleMaterial(color math32.Color4, useColorSSBO bool) *ParticleMaterial {

	m := new(ParticleMaterial)
	c := color.ToColor()
	m.customColor = useColorSSBO
	if m.customColor {
		m.Standard.Init("particlecolored", &c)
	} else {
		m.Standard.Init("particle", &c)
	}
	m.SetOpacity(color.A)
	m.SetParticleSize(-1.0) // -1.0: Constant size of 1 pixel, no matter the distance

	return m
}

// SetSize sets the relative particle size depending on distance on to camera.
// If size==-1, a constant size of one pixel is applied
func (m *ParticleMaterial) SetParticleSize(size float32) {
	m.udata.psize = size
}

func (m *ParticleMaterial) RenderSetup(gl *gls.GLS) {
	m.Standard.RenderSetup(gl)
}
