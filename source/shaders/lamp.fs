#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
};

uniform vec3 viewPos;
uniform sampler2D texture_diffuse;
uniform vec3 pointLightOff;
uniform vec3 spotLightOff;
uniform SpotLight spotLight;

vec3 CalcSpotLight(SpotLight light, vec3 fragPos, vec3 viewDir);

void main()
{    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result= vec3(texture(texture_diffuse, TexCoords))*pointLightOff*0.8;
    result += CalcSpotLight(spotLight, FragPos, viewDir)*spotLightOff;    
    FragColor =  vec4(result, 1.0);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse* vec3(texture(texture_diffuse, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    return (ambient + diffuse);//+ specular);
}