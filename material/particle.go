package material

import (
	"github.com/g3n/engine/gls"
	"github.com/g3n/engine/math32"
)

type ParticleMaterial struct {
	Standard // Embedded standard material
	color    math32.Color4
	uniColor gls.Uniform
}

func NewParticleMaterial(color math32.Color4) *ParticleMaterial {

	m := new(ParticleMaterial)
	c := color.ToColor()
	m.Standard.Init("particle", &c)
	m.SetOpacity(color.A)
	m.SetParticleSize(1.0)

	//m.uniColor.Init("Color")
	m.color = color
	return m
}

// SetSize sets the point size
func (m *ParticleMaterial) SetParticleSize(size float32) {

	m.udata.psize = size
}

func (m *ParticleMaterial) RenderSetup(gl *gls.GLS) {

	m.Standard.RenderSetup(gl)
	//gl.Uniform4fv(m.uniColor.Location(gl), 1, &m.color.R)
}
