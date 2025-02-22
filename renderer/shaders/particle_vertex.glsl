#include <attributes>

// Model uniforms
uniform mat4 MVP;
uniform mat4 MV;

#include <material>

// Output variables for Fragment shader
out vec3 Color;

void main() {

    // Transform vertex position to camera coordinates
    vec4 pos = MVP * vec4(VertexPosition, 1.0);
    gl_Position = pos;

    // Sets the size of the rasterized point decreasing with distance
    vec4 posMV = MV * vec4(VertexPosition, 1.0);
    gl_PointSize = MatPointSize / -posMV.z;

    Color = MatDiffuseColor; //MatEmmissiveColor; //VertexColor;
}
