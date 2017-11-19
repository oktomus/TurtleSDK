#version 330 core

// INPUT                                     
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// UNIFORM                                   
// - camera                                  
uniform mat4 view;                     
uniform vec3 camUp;                     // Worldspace
uniform vec3 camRight;                  // Worldspace 
uniform mat4 projection;               
uniform vec3 billboardCenter; // In wordspace

// OUTPUT                                    
out vec3 FragPos;
out vec2 TexCoords;

// MAIN                                      
void main( void )                             
{                                             
    gl_PointSize = 20.0; 

    TexCoords = aTexCoords;
    FragPos = billboardCenter + camRight * aPos.x + camUp * aPos.y;
    //FragPos = aPos;
    //billboardCenter + camRight  * aPos.x + camUp * aPos.y;
    gl_Position = projection * view * vec4( FragPos, 1.0 );
}                                                                                     
