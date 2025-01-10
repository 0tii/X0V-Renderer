#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

#define MAX_DIRECTIONAL_LIGHTS 32
#define MAX_POINT_LIGHTS 512
#define MAX_SPOT_LIGHTS 256

struct DirectionalLight {
  vec3 direction;
  float padding1;
  vec3 diffuse;
  float padding3;
  vec3 specular;
  float padding4;
  vec3 ambient;
  float padding2;
};

struct SpotLight {
  vec3 position;
  float padding1;
  vec3 direction;
  float padding2;
  float cutOff;
  float outerCutOff;
};

struct PointLight {
  vec3 position;
  float padding1;

  float constant;
  float linear;
  float quadratic;
  float padding2;

  vec3 diffuse;
  float padding3;
  vec3 ambient;
  float padding4;
  vec3 specular;
  float padding5;
};

layout(std140) uniform LightData {
  DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
  PointLight pointLights[MAX_POINT_LIGHTS];
  SpotLight spotLights[MAX_SPOT_LIGHTS];
  int numDirectionalLights;
  int numPointLights;
  int numSpotLights;
  float padding1;
};

uniform int dirLightIndices[MAX_DIRECTIONAL_LIGHTS];
uniform int numApplicableDirLights;

uniform int pointLightIndices[MAX_POINT_LIGHTS];
uniform int numApplicablePointLights;

uniform int spotLightIndices[MAX_SPOT_LIGHTS];
uniform int numApplicableSpotLights;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emissive;
  float shininess;
};

uniform Material material;

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
float CalculateSpotLightIntensity(SpotLight light, vec3 fragPos, vec3 diffuseColor, vec3 specularColor);

void main() {
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(-FragPos);

  vec3 diffuseTexelColor = vec3(texture(material.diffuse, TexCoord));
  vec3 specularTexelColor = vec3(texture(material.specular, TexCoord));
  vec4 emissionTexelColor = texture(material.emissive, TexCoord);

  vec3 result = vec3(0);

  for(int i = 0; i < numApplicableDirLights; i++) {
    int currentIndex = dirLightIndices[i];
    result += CalculateDirectionalLight(directionalLights[currentIndex], norm, viewDir, diffuseTexelColor, specularTexelColor);
  }

  // for(int i = 0; i < numApplicableSpotLights; i++) {
  //   int currentIndex = spotLightIndices[i];
  //   result *= CalculateSpotLightIntensity(spotLights[currentIndex], FragPos, diffuseTexelColor, specularTexelColor);
  // }

  for(int i = 0; i < numApplicablePointLights; i++) {
    int currentIndex = pointLightIndices[i];
    result += CalculatePointLight(pointLights[currentIndex], norm, FragPos, viewDir, diffuseTexelColor, specularTexelColor);
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
  vec3 specular = light.specular * spec * specularColor;

  return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor) {
  // diffuse
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(normal, lightDir), 0.0);

  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

  vec3 ambient = light.ambient * diffuseColor;
  vec3 diffuse = light.diffuse * diff * diffuseColor;
  vec3 specular = light.specular * spec * specularColor;

  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

float CalculateSpotLightIntensity(SpotLight light, vec3 fragPos, vec3 diffuseColor, vec3 specularColor) {
  vec3 lightDir = normalize(light.position - fragPos);
  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;

  return clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
}
