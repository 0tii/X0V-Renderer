#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
  sampler2D diffuse;
  // sampler2D specular;
  float specularIntensity;
};

uniform Material material;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
  // diffuse lighting
  vec3 normalVector = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);

  float ambientLightLevel = 0.2;
  float diffuseLightStrength = max(dot(normalVector, lightDirection), 0);

  // specular lighting
  float specularIntensity = 0.5;
  vec3 viewDirection = normalize(viewPos - FragPos);
  vec3 reflectDirection = reflect(-lightDirection, normalVector);
  float specularComponent = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

  // combining light intensities
  float totalLightIntensity = ambientLightLevel + diffuseLightStrength + specularComponent;

  vec4 diffuseColor = texture(material.diffuse, TexCoord); // pixel color taken from texture at fragment coord

  // vec4 specularColor = texture(material.specular, TexCoord);

  FragColor = vec4(diffuseColor.x * totalLightIntensity, diffuseColor.y * totalLightIntensity, diffuseColor.z * totalLightIntensity, 1);
};