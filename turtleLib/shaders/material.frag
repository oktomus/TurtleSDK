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

struct SpotLight {      // Spot light
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    LightValue value;
};

struct Material {       // Texture struc
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    float shininess;
}; 

// SIGNATURES

vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 color, vec3 specFactor);
vec3 processPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color, vec3 specFactor);
vec3 processSpotLigh(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color, vec3 specFactor); 
  
// VARIABLES

// In
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// Global
uniform Material material;
//uniform Light light;  
uniform vec3 viewPos;
uniform DirLight dirLight;
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform bool noTexture;

// Out
out vec4 fragmentColor;

// MAIN
void main( void )
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 color;
    vec3 specFactor;

    if(noTexture)
    {
       color = vec3(1.0, 0, 0); 
       specFactor = vec3(1);
    }
    else
    {
        color = vec3(texture(material.texture_diffuse1, TexCoords));
        specFactor = vec3(texture(material.texture_specular1, TexCoords));
    }

    // Dir light first
    vec3 result = processDirLight(dirLight, norm, viewDir, color, specFactor);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += processPointLight(pointLights[i], norm, FragPos, viewDir, color, specFactor);    
    // Spot
    result += processSpotLigh(spotLight, norm, FragPos, viewDir, color, specFactor);

    fragmentColor = vec4(result, 1.0 );
}

// FUNCTIONS
 
vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 color, vec3 specFactor)  // Directional light
{
    // Diffuse factor
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular factor
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Compound
    vec3 ambient = light.value.ambient * color;
    vec3 diffuse = light.value.diffuse * diff * color;
    vec3 specular = light.value.specular * spec * specFactor;

    return (ambient + diffuse + specular);
}

vec3 processPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color, vec3 specFactor)
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
    vec3 ambient = light.value.ambient * color;
    vec3 diffuse = light.value.diffuse * diff * color;
    vec3 specular = light.value.specular * spec * specFactor;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 processSpotLigh(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color, vec3 specFactor)
{

    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.value.ambient * color;
    vec3 diffuse = light.value.diffuse * diff * color;
    vec3 specular = light.value.specular * spec * specFactor;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

