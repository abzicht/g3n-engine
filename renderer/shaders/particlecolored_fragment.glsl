precision highp float;

// Inputs from vertex shader
in vec4 Position;
in vec3 Normal;
in vec2 FragTexcoord;
in vec4 FragParticleColor;
// Final fragment color
out vec4 FragColor;

void main() {
    FragColor = FragParticleColor;
    return;
}
