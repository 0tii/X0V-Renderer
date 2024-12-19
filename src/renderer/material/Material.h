#pragma once

#include <vector>

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

class Material
{
public:
  Material(Shader &fragmentShader, Texture &diffuse, Texture *specular = nullptr);
  ~Material();

  void bind() const;
  void unbind() const;

  // setters
  void setShininess(float shininess);
  void setShader(Shader &shader);
  void setDiffuseTexture(Texture &texture);
  void setSpecularTexture(Texture *texture);

private:
  Shader &shader;
  float shininess = 32.0f;
  Texture &diffuseTexture;
  Texture *specularTexture;
  // some day normal maps...
};