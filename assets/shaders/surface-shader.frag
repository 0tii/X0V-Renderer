#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emissive;
  float shininess;
};

uniform Material material;

struct DirectionalLight {
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform DirectionalLight directionalLight;

struct SpotLight
{
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;
};

uniform SpotLight spotLight;

struct PointLight
{
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
float CalculateSpotLightIntensity(SpotLight light, vec3 fragPos, vec3 diffuseColor, vec3 specularColor);

void main() {
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(- FragPos);

  vec3 diffuseTexelColor = vec3(texture(material.diffuse, TexCoord));
  vec3 specularTexelColor =vec3( texture(material.specular, TexCoord));
  vec4 emissionTexelColor = texture(material.emissive, TexCoord);

  vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDir, diffuseTexelColor, specularTexelColor);

  float spotlightStrength = CalculateSpotLightIntensity(spotLight, FragPos, diffuseTexelColor, specularTexelColor);

  result *= spotlightStrength;

  for(int i = 0; i < NR_POINT_LIGHTS; i++)
  {
    result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir, diffuseTexelColor, specularTexelColor);
  }

  FragColor = vec4(result, 1) + emissionTexelColor;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor) {
  vec3 lightDir = normalize(-light.direction); //! directions must be transformed with w = 0!
  
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);

  // specular highlight
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec3 ambient = light.ambient * diffuseColor;
  vec3 diffuse = light.diffuse * diff * diffuseColor;
  vec3 specular = light.specular *  spec * specularColor;

  return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor)
{
  // diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(normal, lightDir), 0.0);

  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);

  vec3 ambient = light.ambient * diffuseColor;
  vec3 diffuse = light.diffuse * diff * diffuseColor;
  vec3 specular = light.specular * spec * specularColor;

  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0/ (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

float CalculateSpotLightIntensity(SpotLight light, vec3 fragPos, vec3 diffuseColor, vec3 specularColor)
{
  vec3 lightDir = normalize(spotLight.position - fragPos);
  float theta = dot(lightDir, normalize(-spotLight.direction));
  float epsilon = spotLight.cutOff - spotLight.outerCutOff;

  return clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
}
