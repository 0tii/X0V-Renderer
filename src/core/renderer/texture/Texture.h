#pragma once

#include <iostream>
#include <glad/glad.h>

#include "../../../lib/image-loading/stb_image.h"

class Texture
{
public:
  Texture(const char *imagePath, GLenum colorProfile, bool flipped = true);
  ~Texture();

  void bind(unsigned int textureUnit);
  void unbind();

  void setWrappingMode(GLenum modeS, GLenum modeT);
  void setScalingFilter(GLenum minFilter, GLenum magFilter);

private:
  unsigned int textureId = 0;

  unsigned char *imageData;
  int width, height, nrChannels;

  GLint maxUnits;
};