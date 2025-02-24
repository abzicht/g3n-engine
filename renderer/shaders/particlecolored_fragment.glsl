precision highp float;

// Inputs from vertex shader
in vec4 FragParticleColor;
// Final fragment color
out vec4 FragColor;

void main() {
    FragColor = FragParticleColor;
    return;
}
