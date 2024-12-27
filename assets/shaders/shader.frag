#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

struct Material
{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

uniform Material material;

uniform float blendFactor;

void main()
{
  vec4 diffuseColor = texture(material.diffuse, TexCoord);
  vec4 specularColor = texture(material.specular, TexCoord);
  FragColor = diffuseColor;
};