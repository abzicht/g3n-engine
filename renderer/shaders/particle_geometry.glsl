layout(points) in;                     // Receives single points
layout(triangle_strip, max_vertices = 64) out;

in VS_OUT {
    vec4 color;
    float size;
} gs_in[];

uniform int VertexCount;
layout(std430, binding = 2) buffer ShapeBuffer {
    vec3 offsets[];
};


out vec4 Color;
//out vec2 texCoords; // Pass to fragment shader


void emitVertex(vec3 offset, vec4 color) {
    gl_Position = (gl_in[0].gl_Position + vec4(offset, 0.0));
    Color = color;
    EmitVertex();
}

void main() {
    vec4 baseColor = gs_in[0].color;
    float s = gs_in[0].size;
    if (VertexCount == 0) {
        emitVertex(vec3(-s, -s, 0.0), baseColor);
        emitVertex(vec3( s, -s, 0.0), baseColor);
        emitVertex(vec3( 0.0, s, 0.0), baseColor);
    } else {
        for (int i = 0; i < VertexCount; i++) {
            vec3 offset = offsets[i] * s;
            emitVertex(offset, baseColor);
        }
    }
    EndPrimitive();
}
