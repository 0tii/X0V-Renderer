/*
  File: TextureAtlas.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/25/2024
*/

#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

class TextureAtlas
{
public:
  TextureAtlas(const std::vector<std::string> &texturePaths, int textureSize);
  ~TextureAtlas();

  void buildAtlas();
  unsigned int getTextureID() const;
  glm::vec4 getUVRegion(int textureIndex) const;

private:
  std::vector<std::string> texturePaths;
  int textureSize, atlasSize;
  unsigned int atlasTextureID;
};