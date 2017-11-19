#version 330 core

// STRUCTS

struct Material {       // Texture struc
    sampler2D texture_diffuse1;
}; 

  
// VARIABLES

// In
in vec2 TexCoords;

// Global
uniform Material material;
uniform vec3 fill;

// Out
out vec4 fragmentColor;

// MAIN
void main( void )
{
    vec3 color = fill * texture(material.texture_diffuse1, TexCoords).a;
    fragmentColor = vec4(color, 1.0);
    fragmentColor.a = texture(material.texture_diffuse1, TexCoords).a;
}
