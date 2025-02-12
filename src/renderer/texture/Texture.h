#pragma once

#include <iostream>
#include <glad/glad.h>
#include <stbi/stb_image.h>

class Texture
{
public:
  Texture(const char *imagePath, GLenum colorProfile, bool flipped = true);
  Texture(GLuint textureId);
  ~Texture();

  void bind(unsigned int textureUnit = 0);
  void unbind();

  void setWrappingMode(GLenum modeS, GLenum modeT);
  void setScalingFilter(GLenum minFilter, GLenum magFilter);

  // getters
  unsigned int getTextureId() const;

private:
  unsigned int textureId = 0;
  GLint maxUnits;
};