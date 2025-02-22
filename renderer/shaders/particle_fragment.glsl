precision highp float;

#include <material>

in vec3 Color;
// Final fragment color
out vec4 FragColor;

void main() {

    // Final fragment color
    //FragColor = vec4(Color, MatOpacity);
    FragColor = vec4(1);

    //vec4 matDiffuse = vec4(MatDiffuseColor, MatOpacity);
    //vec4 matAmbient = vec4(MatAmbientColor, MatOpacity);
    //FragColor = matDiffuse + matAmbient;
}
