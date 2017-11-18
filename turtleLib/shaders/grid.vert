#version 330 core

uniform mat4 projection;
uniform mat4 view;

uniform ivec2 dim;

const vec2 triOffset[] = vec2[](
        vec2(0,0),
        vec2(0,0.1),
        vec2(0.1,0.1),
        vec2(0,0),
        vec2(0.1,0.1),
        vec2(0.1,0));

void main()
{
    gl_PointSize = 20.0; 
    int triVert = gl_VertexID % 6;
    int gridIndex = gl_VertexID / 6;
    vec2 coord = vec2(gridIndex / 1, gridIndex % 1);
    coord = (coord + triOffset[triVert]) / vec2(dim);
    vec4 esVert = view * vec4(coord * 2.0 - 1.0, 0.0, 1.0);
    gl_Position = projection * esVert;
    //gl_Position = projection * view * vec4(vec3(gl_VertexID/100.0), 1.0);
}
