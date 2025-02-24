package material

import (
	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/math32"
)

type ParticleMaterial struct {
	Standard // Embedded standard material
}

// Create a new particle material with the given color and the shader program
// "particle". Use SetShader to use a custom particle shader program.
func NewParticleMaterial(color math32.Color4) *ParticleMaterial {

	m := new(ParticleMaterial)
	c := color.ToColor()
	m.Standard.Init("particle", &c)
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
