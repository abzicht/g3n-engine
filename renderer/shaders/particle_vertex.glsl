// Model uniforms
uniform mat4 MM;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM;
uniform bool IsInstanced; // Use an instanced shape instead of only drawing
                          // pixels

#include <attributes>
#include <material>

layout(std430, binding = 0) buffer ParticlePos {
    vec3 positions[];
};
layout(std430, binding = 1) buffer ParticleColor {
    vec4 colors[];
};


// Output variables for Fragment shader
out vec4 Position;
out vec3 Normal;
out vec2 FragTexcoord;
out vec4 FragParticleColor;

void main() {
    // id is set depending on whether we render objects or only pixels
    uint id = IsInstanced ? gl_InstanceID : gl_VertexID;
    if (id < colors.length()) {
        FragParticleColor = colors[id];
    } else {
        FragParticleColor = vec4(0);
    }

    //if (id >= positions.length()) {return;}

    vec3 pos = positions[id];
    if (IsInstanced) {
        pos +=  VertexPosition;
    }
    // Transform vertex position to camera coordinates
    Position = MV * vec4(pos, 1.0);
    Normal = normalize(NM * VertexNormal);
    vec2 texcoord = VertexTexcoord;
    #if MAT_TEXTURES > 0
        // Flip texture coordinate Y if requested.
        if (MatTexFlipY(0)) {
            texcoord.y = 1.0 - texcoord.y;
        }
    #endif
    FragTexcoord = texcoord;

    mat4 finalWorld = mat4(1.0);
    #include <morphtarget_vertex>
    #include <bones_vertex>
    gl_Position = MVP * finalWorld * vec4(pos, 1.0);

    if (!IsInstanced) {
        // If we don't have shapes but only points, we set their sizes
        // Sets the size of the rasterized point decreasing with distance
        vec4 posMV = MV * vec4(positions[id], 1.0);
        if (MatPointSize == -1.0) {
            gl_PointSize = 1.0;
        } else {
            gl_PointSize = MatPointSize / -posMV.z;
        }
    }
}
