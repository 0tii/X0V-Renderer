#include "Material.h"

Material::Material(Shader &fragmentShader, Texture &diffuse, Texture *specular)
    : shader(fragmentShader), diffuseTexture(diffuse), specularTexture(specular)
{
}

Material::~Material()
{
  if (specularTexture)
  {
    std::cout << "[Material] Destructor invoked, deleting specular texture" << std::endl;
    delete specularTexture;
  }
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

Shader &Material::getShader() const
{
  return shader;
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
  if (specularTexture)
  {
    delete specularTexture;
  }
  this->specularTexture = texture;
}

void Material::setSpecularTexture(unsigned int texture)
{
  if (specularTexture)
  {
    delete specularTexture;
  }
  this->specularTexture = new Texture(texture);
}
