#include "Material.h"

Material::Material(Shader &fragmentShader, Texture &diffuse, Texture *specular)
    : shader(fragmentShader), diffuseTexture(diffuse), specularTexture(specular ? specular : nullptr), emissiveTexture(nullptr)
{
}

Material::~Material()
{
  if (specularTexture)
  {
    // std::cout << "[Material] Destructor invoked, deleting specular texture" << std::endl;
    delete specularTexture;
  }
  if (emissiveTexture)
  {
    // std::cout << "[Material] Destructor invoked, deleting emissive texture" << std::endl;
    delete emissiveTexture;
  }
}

void Material::bind() const
{
  shader.use();

  // bind diffuse tetxure
  diffuseTexture.bind(0);
  shader.setInt("material.diffuse", 0);

#ifdef DEBUG_VERBOSE
  glBindTexture(GL_TEXTURE_2D, diffuseTexture->getTextureId());
  int width, height, channels;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &channels);
  std::cout << "Binding diffuse texture: " << diffuseTexture->getTextureId() << std::endl;
  std::cout << "Diffuse texture size: " << width << "x" << height << " channels: " << channels << std::endl;
#endif

  // bind specular texture
  if (specularTexture)
  {
    specularTexture->bind(1);
    shader.setInt("material.specular", 1);

#ifdef DEBUG_VERBOSE
    glBindTexture(GL_TEXTURE_2D, specularTexture->getTextureId());
    int width, height, channels;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &channels);
    std::cout << "Binding specular texture: " << specularTexture->getTextureId() << std::endl;
    std::cout << "Specular texture size: " << width << "x" << height << " channels: " << channels << std::endl;
#endif
  }

  if (emissiveTexture)
  {
    emissiveTexture->bind(2);
    shader.setInt("material.emissive", 2);

#ifdef DEBUG_VERBOSE
    glBindTexture(GL_TEXTURE_2D, emissiveTexture->getTextureId());
    int width, height, channels;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &channels);
    std::cout << "binding emissive texture: " << emissiveTexture->getTextureId() << std::endl;
    std::cout << "Emissive texture size: " << width << "x" << height << " channels: " << channels << std::endl;
#endif
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
  if (emissiveTexture)
  {
    emissiveTexture->unbind();
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

void Material::setEmissiveTexture(unsigned int textureId)
{
  if (emissiveTexture)
  {
    delete emissiveTexture;
  }
  this->emissiveTexture = new Texture(textureId);
}
