#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
  vec3 normalVector = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);

  float diff = max(dot(normalVector, lightDirection), 0.0);
  vec3 diffuse = diff * lightColor;

  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;
  FragColor = vec4(result, 1.0);
}