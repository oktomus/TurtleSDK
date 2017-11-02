#version 330 core

// INPUT
in vec3 position;

// VARS
// - camera                                  
uniform mat4 viewMatrix;                     
uniform mat4 projectionMatrix;               
// - 3D model                                
uniform mat4 modelMatrix;                    

// OUTPUT

// PROCESS
void main( void )
{
    gl_PointSize = 20.0; 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( position, 1.0 );     
}
