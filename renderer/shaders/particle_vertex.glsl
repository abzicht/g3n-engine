

layout(location = 0) in vec3 VertexPosition;
// Model uniforms
uniform mat4 MVP;
uniform mat4 MV;

#include <material>

layout(std430, shared, binding = 0) buffer VertexPos {
    vec3 positions[];
};

// Output variables for Fragment shader
out vec3 Color;
out vec3 Normal;

void main() {

    // Transform vertex position to camera coordinates
    vec4 Position = MVP * vec4(positions[gl_VertexID], 1.0);
    gl_Position = Position;

    // Sets the size of the rasterized point decreasing with distance
    vec4 posMV = MV * vec4(positions[gl_VertexID], 1.0);
    if (MatPointSize == -1.0) {
        gl_PointSize = 1.0;
    } else {
        gl_PointSize = MatPointSize / -posMV.z;
    }
    Color = MatDiffuseColor; //MatEmmissiveColor; //VertexColor;
}
