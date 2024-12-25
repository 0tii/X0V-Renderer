/*
  File: TextureAtlas.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/25/2024
*/

#include "TextureAtlas.h"

#include <glad/glad.h>
#include <stbi/stb_image.h>
#include <iostream>

TextureAtlas::TextureAtlas(const std::vector<std::string> &texturePaths, int textureSize)
    : texturePaths(texturePaths), textureSize(textureSize), atlasSize(0), atlasTextureID(0)
{
  int gridSize = static_cast<int>(std::ceil(std::sqrt(texturePaths.size())));
  atlasSize = gridSize * textureSize;
}

TextureAtlas::~TextureAtlas()
{
  std::cout << "Destroying TextureAtlas and removing texture from GPU" << std::endl;
  if (atlasTextureID)
    glDeleteTextures(1, &atlasTextureID);
}

void TextureAtlas::buildAtlas()
{
  glGenTextures(1, &atlasTextureID);
  glBindTexture(GL_TEXTURE_2D, atlasTextureID);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlasSize, atlasSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  for (int i = 0; i < texturePaths.size(); ++i)
  {
    int width, height, channels;
    unsigned char *imageData = stbi_load(texturePaths[i].c_str(), &width, &height, &channels, 0);

    if (!imageData || width != textureSize || height != textureSize)
    {
      std::cerr << "Error loading texture: " << texturePaths[i] << std::endl;
      stbi_image_free(imageData);
      continue;
    }

    int gridX = i % (atlasSize / textureSize);
    int gridY = i / (atlasSize / textureSize);

    int xOffset = gridX * textureSize;
    int yOffset = gridY * textureSize;

    glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, textureSize, textureSize, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);
  }

  glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int TextureAtlas::getTextureID() const
{
  return atlasTextureID;
}

glm::vec4 TextureAtlas::getUVRegion(int textureIndex) const
{
  int gridSize = atlasSize / textureSize;
  int gridX = textureIndex % gridSize;
  int gridY = textureIndex / gridSize;

  float uvWidth = 1.0f / gridSize;
  float uvHeight = uvWidth;

  float uMin = gridX * uvWidth;
  float vMin = gridY * uvHeight;

  return glm::vec4(uMin, vMin, uvWidth, uvHeight);
}