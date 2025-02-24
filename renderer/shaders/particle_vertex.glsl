// Model uniforms
uniform mat4 MM;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM;
uniform bool IsInstanced;

#include <attributes>
#include <material>

layout(std430, shared, binding = 0) buffer ParticlePos {
    vec3 positions[];
};
layout(std430, shared, binding = 1) buffer ParticleColor {
    vec4 colors[];
};


// Output variables for Fragment shader
//out vec4 Position;
//out vec3 Normal;
//out vec2 FragTexcoord;
out vec4 Color;

void main() {
    // id is set depending on whether we render objects or only pixels
    uint id = IsInstanced ? gl_InstanceID : gl_VertexID;
    if (id < colors.length()) {
        Color = colors[id];
    } else {
        Color = vec4(-1);
    }

    if (id >= positions.length()) {return;}

    vec3 pos = positions[id];
    if (IsInstanced) {
        pos +=  VertexPosition;
    }
    gl_Position = MVP * vec4(pos, 1.0);
    //// Transform vertex position to camera coordinates
    //Position = MV * vec4(pos, 1.0);
    //Normal = normalize(NM * VertexNormal);
    //// Tex coords
    //vec2 texcoord = VertexTexcoord;
    //#if MAT_TEXTURES > 0
    //// Flip texture coordinate Y if requested.
    //if (MatTexFlipY(0)) {
    //    texcoord.y = 1.0 - texcoord.y;
    //}
    //#endif
    //FragTexcoord = texcoord;

    //mat4 finalWorld = mat4(1.0);
    //#include <morphtarget_vertex>
    //#include <bones_vertex>
    //gl_Position = MVP * vec4(pos, 1.0);

    if (!IsInstanced) {
        // If we don't have shapes but only points, we set their sizes
        // Sets the size of the rasterized point decreasing with distance
        vec4 posMV = MV * vec4(pos, 1.0);
        if (MatPointSize == -1.0) {
            gl_PointSize = 1.0;
        } else {
            gl_PointSize = MatPointSize / -posMV.z;
        }
    }
}
