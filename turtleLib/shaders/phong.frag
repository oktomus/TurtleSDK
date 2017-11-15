#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 fragmentColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

// MAIN
void main( void )
{
    // Ambient
    float ambientIntensity = 0.1;
    vec3 ambient = lightColor * ambientIntensity;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  


    // Result
    vec3 color = (ambient + diffuse + specular) * objectColor;
    fragmentColor = vec4(color, 1.0 );
}

