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
  void setAmbientColor(Color color);

private:
  Shader &shader;
  float shininess = 32.0f;
  Texture &diffuseTexture;
  Texture *specularTexture;
  Color ambientColor = Color(0.2f);
  // some day normal maps...
};

using uMaterialPtr = std::unique_ptr<Material>;
using sMaterialPtr = std::shared_ptr<Material>;