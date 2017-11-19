#version 330 core

// STRUCTS

struct LightValue {     // Light compounds
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {       // Directional light
    vec3 direction;
    LightValue value;
};

struct PointLight {     // Point light
    vec3 position;
    float constant;
    float linear;
    float quadratic;  
    LightValue value;
};  

struct Material {       // Texture struc
    sampler2D texture_height1;
    float shininess;
}; 

// SIGNATURES

vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir);                        // Directional light
vec3 processPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);      // Point light
  
// VARIABLES
uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 groundColor1;
uniform vec3 outsideColor;

// In
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Out
out vec4 fragmentColor;

// MAIN
void main( void )
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Dir light first
    vec3 result = processDirLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += processPointLight(pointLights[i], norm, FragPos, viewDir);    

    fragmentColor = vec4(result, 1.0 );
}

vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir)                         // Directional light
{
    // Diffuse factor
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular factor
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Compound
    vec3 ambient = light.value.ambient * groundColor1;
    vec3 diffuse = light.value.diffuse * diff * groundColor1;
    vec3 specular = light.value.specular * spec * groundColor1;

    return (ambient + diffuse + specular);
}

vec3 processPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)       // Directional light
{
    // Diffuse factor
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular factor
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Fade
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist +
            light.quadratic * (dist * dist));
    // Compound
    vec3 ambient = light.value.ambient * groundColor1;
    vec3 diffuse = light.value.diffuse * diff * groundColor1;
    vec3 specular = light.value.specular * spec * groundColor1;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}


