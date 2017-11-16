#version 330 core

// INPUT                                     
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

// UNIFORM                                   
// - camera                                  
uniform mat4 view;                     
uniform mat4 projection;               
uniform mat4 model;                    
uniform vec3 lightPos;

// OUTPUT                                    
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

// MAIN                                      
void main( void )                             
{                                             
    gl_PointSize = 20.0; 
    gl_Position = projection * view * model * vec4( aPos, 1.0 );
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal =  mat3(transpose(inverse(view * model))) * aNormal;  
    TexCoords = aTexCoords;
}                                                                                     
