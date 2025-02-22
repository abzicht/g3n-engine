precision highp float;

#include <lights>
#include <material>
#include <phong_model>

in vec3 Color;
// Final fragment color
out vec4 FragColor;

void main() {

    // Final fragment color
    vec4 matDiffuse = vec4(MatDiffuseColor, MatOpacity);
    vec4 matAmbient = vec4(MatAmbientColor, MatOpacity);
    FragColor = matDiffuse + matAmbient;
}
