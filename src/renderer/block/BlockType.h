/*
  File: BlockType.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/26/2024
*/

#pragma once

#include <string>
#include <iostream>

#include "renderer/shader/ShaderType.h"

struct BlockType
{
public:
  BlockType() = default;
  BlockType(std::string textureName, ShaderType shaderType = ShaderType::Surface, bool emit = false);
  BlockType(std::string textureY, std::string textureSides, ShaderType shaderType = ShaderType::Surface);
  BlockType(std::string textureTop, std::string textureBottom,
            std::string textureSides, ShaderType shaderType = ShaderType::Surface);
  BlockType(std::string textureTop, std::string textureBottom, std::string textureNorth,
            std::string textureEast, std::string textureSouth, std::string textureWest,
            ShaderType shaderType = ShaderType::Surface);

  std::string top, bottom, north, east, south, west;
  ShaderType shaderType;
  bool emit = false;

  void validate() const;
};