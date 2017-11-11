#version 330 core

uniform vec3 meshColor;

out vec4 fragmentColor;

// MAIN
void main( void )
{
    fragmentColor = vec4( meshColor, 1.0 );
}

