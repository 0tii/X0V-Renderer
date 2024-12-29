#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

struct Material
{
  vec4 ambient;
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

uniform Material material;

uniform vec3 lightColor;

void main()
{
  // pixel color taken from texture at fragment coord
  vec4 diffuseColor = texture(material.diffuse, TexCoord); 
  
  // -- vec4 specularColor = texture(material.specular, TexCoord);
  vec4 specularColor = vec4(1.0); // !! <-- will be passed as texture(material.specular, TexCoord); from texture

  vec4 ambient = vec4(lightColor, 1) * material.ambient;

  // diffuse lighting
  vec3 normalVector = normalize(Normal);
  vec3 lightDirection = normalize(LightPos - FragPos);
  float diffuseLightStrength = max(dot(normalVector, lightDirection), 0);
  vec4 diffuse = vec4(lightColor, 1) * (diffuseLightStrength);

  // specular
  vec3 viewDirection = normalize(-FragPos); // we are in view space, so we take -FragPos only
  vec3 reflectDirection = reflect(-lightDirection, normalVector);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
  vec4 specular = vec4(lightColor, 1) * (spec * specularColor);

  vec4 finalLight = ambient + diffuse + specular;
  FragColor = diffuseColor * finalLight;
}