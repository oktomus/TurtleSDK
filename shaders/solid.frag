#version 130

// INPUT

// VARS
uniform vec4 color;

// OUTPUT
out vec4 fragmentColor;

// PROCESS
void main( void )
{
    fragmentColor = color;
}
