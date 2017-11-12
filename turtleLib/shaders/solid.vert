#version 330 core

// INPUT
layout (location = 0) in vec3 aPos;

// VARS

// OUTPUT

// PROCESS
void main( void )
{
    gl_PointSize = 10.0; 
    gl_Position = vec4( aPos, 1.0 );     
}
