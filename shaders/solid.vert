#version 330 core

// INPUT
in vec3 position;

// VARS

// OUTPUT

// PROCESS
void main( void )
{
    gl_Position = vec4(position, 1.0) ;
}
