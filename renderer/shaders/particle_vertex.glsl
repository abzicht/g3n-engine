// Model uniforms
uniform mat4 MVP;
uniform mat4 MV;

#include <material>

layout(std430, shared, binding = 0) buffer ParticlePos {
    vec3 positions[];
};
layout(std430, shared, binding = 1) buffer ParticleColor {
    vec4 colors[];
};


out VS_OUT {
    vec4 color;
    float size;
} vs_out;

void main() {
    uint id = gl_VertexID;
    if (id < colors.length()) {
        vs_out.color = colors[id];
    } else {
        vs_out.color = vec4(-1);
    }


    // Transform vertex position to camera coordinates
    vec3 pos = positions[id];
    vec4 Position = MVP * vec4(pos, 1.0);
    gl_Position = Position;

    // Sets the size of the rasterized point decreasing with distance
    vec4 posMV = MV * vec4(pos, 1.0);
    if (MatPointSize == -1.0) {
        vs_out.size = 1.0;
    } else {
        vs_out.size = MatPointSize / -posMV.z;
    }
}
