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

vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir);                        // Directional light
vec3 processPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);      // Point light
vec3 processSpotLigh(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);         // Spot Light
  
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
    // Spot
    //vec3 result = processSpotLigh(spotLight, norm, FragPos, viewDir);

    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir); 
    //// Ambient
    ////vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));

    //// Diffuse
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));

    //// Specular
    //vec3 reflectDir = reflect(-lightDir, norm);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

    //// Result
    //vec3 color = ambient + diffuse + specular;
    fragmentColor = vec4(result, 1.0 );
}

// FUNCTIONS
 
vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir)                         // Directional light
{
    // Diffuse factor
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular factor
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Compound
    vec3 ambient = light.value.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse = light.value.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.value.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

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
    vec3 ambient = light.value.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse = light.value.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.value.specular * spec * vec3(texture(material.texture_specular1, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 processSpotLigh(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)           // Spot Light
{

    vec3 lightDir = normalize(light.position - fragPos);

    float theta = dot(lightDir, normalize(-light.direction));

    if(theta > light.cutOff) 
    {       
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 ambient = light.value.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
        vec3 diffuse = light.value.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
        vec3 specular = light.value.specular * spec * vec3(texture(material.texture_specular1, TexCoords));
        return ambient + diffuse + specular;
    }
    else  // else, use ambient light so scene isn't completely dark outside the spotlight.
        return vec3(1);

    /*
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
    vec3 ambient = light.value.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 diffuse = light.value.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));
    vec3 specular = light.value.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
    */
}

