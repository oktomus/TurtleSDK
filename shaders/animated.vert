#version 330 core

// INPUT                                     
layout (location = 0) in vec3 aPos;

// UNIFORM                                   
// - camera                                  
uniform mat4 viewMatrix;                     
uniform mat4 projectionMatrix;               
// - 3D model                                
uniform mat4 modelMatrix;                    
// - animation                               
uniform float time;                          

// OUTPUT                                    

// MAIN                                      
void main( void )                             
{                                             
    gl_PointSize = 20.0; 
#if 1                                                                                 
        // Use animation                                                                  
        float amplitude = 1.0;                                                            
    float frequency = 0.5;                                                            
    float height = amplitude * sin( 2.0 * 3.141592 * frequency * ( time ) );  
    vec3 pos = vec3( aPos.x, aPos.y + height, aPos.z );                   
    // Send aPos to Clip-space                                                    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( pos, 1.0 );     
#else                                                                                 
    // Send aPos to Clip-space                                                    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( aPos, 1.0 );
#endif                                                                                
}                                                                                     
