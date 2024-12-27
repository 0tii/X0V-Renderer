/*
  File: TextureAtlas.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/25/2024
*/

#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class TextureAtlas
{
public:
  TextureAtlas(const std::unordered_map<std::string, std::string> &texturePaths, int textureSize);
  ~TextureAtlas();

  void buildAtlas();
  unsigned int getTextureID() const;
  glm::vec4 getUVRegion(std::string name) const;

private:
  std::unordered_map<std::string, std::string> texturePaths;
  std::unordered_map<std::string, glm::vec4> uvRegions;
  int textureSize, atlasSize, gridSize;
  unsigned int atlasTextureID;
  bool isBuilt = false;

  bool validateAtlas() const;
};