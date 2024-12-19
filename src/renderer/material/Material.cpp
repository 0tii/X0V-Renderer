#include "Material.h"

Material::Material(Shader &fragmentShader, Texture &diffuse, Texture *specular)
    : shader(fragmentShader), diffuseTexture(diffuse), specularTexture(specular)
{
}

Material::~Material()
{
}

void Material::bind() const
{
  shader.use();

  // bind diffuse tetxure
  diffuseTexture.bind(0);
  shader.setInt("material.diffuse", 0);

  // bind specular texture
  if (specularTexture)
  {
    specularTexture->bind(1);
    shader.setInt("material.specular", 1);
  }

  shader.setFloat("material.shininess", shininess);
}

void Material::unbind() const
{
  diffuseTexture.unbind();
  if (specularTexture)
  {
    specularTexture->unbind();
  }
}

void Material::setShininess(float shininess)
{
  this->shininess = shininess;
}

void Material::setShader(Shader &shader)
{
  this->shader = shader;
}

void Material::setDiffuseTexture(Texture &texture)
{
  this->diffuseTexture = texture;
}

void Material::setSpecularTexture(Texture *texture)
{
  this->specularTexture = texture;
}