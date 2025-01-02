#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emissive;
  float shininess;
};

struct Light
{
  vec3 position;

  vec3 ambient; // ambient light color, usually set to dim value
  vec3 diffuse; // lights color
  vec3 specular; // specular intensity usually kept at vec3(1)

  float constant;
  float linear;
  float quadratic;
};

uniform mat4 view;

uniform Light light;
uniform Material material;

void main()
{
  vec3 lightPos  = vec3(view * vec4(light.position, 1.0));

  // pixel color taken from texture at fragment coord
  vec4 diffuseColor = texture(material.diffuse, TexCoord); 
  vec4 specularColor = clamp(texture(material.specular, TexCoord) + vec4(0.15), 0.0, 1.0); // small bump because maps are too dark
  vec4 emissiveColor = texture(material.emissive, TexCoord);

  vec4 ambient = vec4(light.ambient, 1) * diffuseColor;

  // diffuse lighting
  vec3 normalVector = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);
  float diffuseLightStrength = max(dot(normalVector, lightDirection), 0);
  vec4 diffuse = vec4(light.diffuse, 1) * (diffuseLightStrength * diffuseColor);

  // specular
  vec3 viewDirection = normalize(-FragPos); // we are in view space, so we take -FragPos only
  vec3 reflectDirection = reflect(-lightDirection, normalVector);
  float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), max(material.shininess, 0.01));
  vec4 specular = vec4(light.specular, 1) * (spec * specularColor);

  // attenuation
  float distance = length(lightPos - FragPos);
  float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  vec4 finalLight = ((ambient + diffuse + specular) * attenuation) + emissiveColor;
  FragColor = vec4(finalLight.rgb, 1.0);
}