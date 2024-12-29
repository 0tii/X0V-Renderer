#pragma once

#include <vector>

#include "renderer/shader/Shader.h"
#include "renderer/texture/Texture.h"
#include "renderer/color/Color.h"

class Material
{
public:
  Material(Shader &fragmentShader, Texture &diffuse, Texture *specular = nullptr);
  ~Material();

  void bind() const;
  void unbind() const;

  // getters
  Shader &getShader() const;

  // setters
  void setShininess(float shininess);
  void setShader(Shader &shader);
  void setDiffuseTexture(Texture &texture);
  void setSpecularTexture(Texture *texture);
  void setSpecularTexture(unsigned int textureId);

private:
  Shader &shader;
  float shininess = 128.0f;
  Texture &diffuseTexture;
  Texture *specularTexture;
  // some day normal maps...
};

using uMaterialPtr = std::unique_ptr<Material>;
using sMaterialPtr = std::shared_ptr<Material>;