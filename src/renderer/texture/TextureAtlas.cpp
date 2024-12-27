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

TextureAtlas::TextureAtlas(const std::unordered_map<std::string, std::string> &texturePaths, int textureSize)
    : texturePaths(texturePaths), textureSize(textureSize), atlasSize(0), atlasTextureID(0)
{
  this->gridSize = static_cast<int>(std::ceil(std::sqrt(texturePaths.size())));
  this->atlasSize = gridSize * textureSize;
  this->buildAtlas();
}

TextureAtlas::~TextureAtlas()
{
  std::cout << "Destroying TextureAtlas and removing texture from GPU" << std::endl;
  if (atlasTextureID)
    glDeleteTextures(1, &atlasTextureID);
}

void TextureAtlas::buildAtlas()
{
  std::cout << "[TextureAtlas] stitching textures." << std::endl;

  glGenTextures(1, &atlasTextureID);
  glBindTexture(GL_TEXTURE_2D, atlasTextureID);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlasSize, atlasSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int i = 0;
  for (const auto &[textureName, path] : texturePaths)
  {
    int width, height, channels;
    unsigned char *imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!imageData || width != textureSize || height != textureSize)
    {
      std::cerr << "Error loading texture: " << textureName << std::endl;
      stbi_image_free(imageData);
      continue;
    }

    int gridX = i % (atlasSize / textureSize); // calculate the x-position on the atlas grid
    int gridY = i / (atlasSize / textureSize); // calculate the y position on the atlas grid

    int xOffset = gridX * textureSize;
    int yOffset = gridY * textureSize;

    glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, textureSize, textureSize, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    // store uv coordinates
    float uvWidth = 1.0f / gridSize;
    float uvHeight = uvWidth;

    this->uvRegions[textureName] = glm::vec4(gridX * uvWidth, gridY * uvHeight, (gridX + 1) * uvWidth, (gridY + 1) * uvHeight);

    stbi_image_free(imageData);

    ++i;

    std::cout << "[TextureAtlas] stitching texture " << i << " of " << texturePaths.size() << " (" << textureName << ")" << std::endl;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  this->isBuilt = true;
}

unsigned int TextureAtlas::getTextureID() const
{
  this->validateAtlas();
  return atlasTextureID;
}

glm::vec4 TextureAtlas::getUVRegion(std::string name) const
{
  if (!this->validateAtlas())
    return glm::vec4(0.0f);

  auto pair = this->uvRegions.find(name);

  if (pair == uvRegions.end())
  {
    std::cerr << "Unable to find key " << name << " in the texture atlas UV regions" << std::endl;
    return glm::vec4(0.0f);
  }

  return pair->second;
}

bool TextureAtlas::validateAtlas() const
{
  if (!isBuilt)
  {
    std::cerr << "[Error] Texture Atlas has not been built yet!" << std::endl;
    return false;
  }
  return true;
}
