#include "Texture.h"

Texture::Texture(const char *imagePath, GLenum colorProfile, bool flipped)
{
  stbi_set_flip_vertically_on_load(flipped);

  int width, height, nrChannels;
  auto imageData = stbi_load(imagePath, &width, &height, &nrChannels, 0);

  if (!imageData)
  {
    std::cout << "Failed to load texture" << std::endl;
    return;
  }

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  // apply default scaling and wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, colorProfile, width, height, 0, colorProfile, GL_UNSIGNED_BYTE, imageData);
  glGenerateMipmap(GL_TEXTURE_2D);

  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxUnits);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(imageData);
}

/// @brief This constructor takes an already prepared texture.
/// It does NOT send texture data to the GPU! It does, however, set up the default scaling and wrapping settings and generates mipmaps.
/// @param textureId textureId of a generated and prepared texture. Must have been sent to the GPU!
Texture::Texture(GLuint textureId)
{
  this->textureId = textureId;
  glBindTexture(GL_TEXTURE_2D, textureId);

  // apply default scaling and wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glGenerateMipmap(GL_TEXTURE_2D);

  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxUnits);

  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
  if (textureId != 0)
  {
    glDeleteTextures(1, &textureId);
  }
}

void Texture::bind(unsigned int unit)
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

// setters
void Texture::setWrappingMode(GLenum modeS, GLenum modeT)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, modeS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, modeT);
}

void Texture::setScalingFilter(GLenum minFilter, GLenum magFilter)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

// getters
unsigned int Texture::getTextureId() const
{
  return textureId;
}