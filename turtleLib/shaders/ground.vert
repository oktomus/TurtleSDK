#version 330 core

struct Material {       // Texture struc
    sampler2D texture_height1;
    float shininess;
}; 

// INPUT                                     
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

// UNIFORM                                   
// - camera                                  
uniform mat4 view;                     
uniform mat4 projection;               
uniform mat4 model;                    

uniform Material material;
uniform float size;
uniform float baseHeight;
uniform float heightFactor;

// OUTPUT                                    
out vec3 Normal;
out vec3 FragPos;
out vec4 FragColor;
out vec2 TexCoords;

// MAIN                                      
void main( void )                             
{                                             

    TexCoords = vec2(
            (aPos.x  + size / 2) / size,
            (aPos.z  + size / 2) / size
            );

    vec3 pos = aPos;
    if(pos.y > baseHeight + 0.001) // Baseline
    {
        pos.y = texture(material.texture_height1, TexCoords).r * (heightFactor);
    }

    FragPos = vec3(model * vec4(pos, 1.0));
    Normal =  mat3(transpose(inverse(model))) * aNormal;  
    gl_Position = projection * view * vec4( FragPos, 1.0 );
}                                                                                     
 
