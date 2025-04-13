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
	colorBuffer *gls.SSBO
}

// Create a new particle material with the given color and the shader program
// "particle" or "particlecolored" if a color buffer is provided. Use SetShader to use a custom particle shader program.
// Set colorBuffer to tell the shader to load custom color data from the SSBO
// instead of rendering the given material
func NewParticleMaterial(color math32.Color4, colorBuffer *gls.SSBO) *ParticleMaterial {

	m := new(ParticleMaterial)
	c := color.ToColor()
	m.colorBuffer = colorBuffer
	if m.colorBuffer != nil {
		m.Standard.Init("particlecolored", &c)
	} else {
		m.Standard.Init("particle", &c)
	}
	m.SetOpacity(color.A)
	m.SetParticleSize(-1.0) // -1.0: Constant size of 1 pixel, no matter the distance

	return m
}

// Replace the color buffer or remove it by passing a nil value
func (m *ParticleMaterial) SetColorBuffer(colorBuffer *gls.SSBO) {
	if colorBuffer == nil {
		m.Standard.SetShader("particle")
		return
	}
	m.colorBuffer = colorBuffer
	m.Standard.SetShader("particlecolored")
}

// SetSize sets the relative particle size depending on distance to camera.
// If size==-1, a constant size of one pixel is applied.
// This function only applies to pixel-particles that do not have own geometries!
func (m *ParticleMaterial) SetParticleSize(size float32) {
	m.udata.psize = size
}
func (m *ParticleMaterial) ParticleSize() float32 {
	return m.udata.psize
}

func (m *ParticleMaterial) RenderSetup(gl *gls.GLS) {
	m.Standard.RenderSetup(gl)
	if m.colorBuffer != nil {
		m.colorBuffer.Bind(gl)
	}
}
