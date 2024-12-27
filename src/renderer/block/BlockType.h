/*
  File: BlockType.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/26/2024
*/

#pragma once

#include <string>
#include <iostream>

struct BlockType
{
public:
  BlockType() = default;
  BlockType(std::string textureName);
  BlockType(std::string textureY, std::string textureSides);
  BlockType(std::string textureTop, std::string textureBottom, std::string textureSides);
  BlockType(std::string textureTop, std::string textureBottom, std::string textureNorth,
            std::string textureEast, std::string textureSouth, std::string textureWest);

  std::string top, bottom, north, east, south, west;

  void validate() const;
};