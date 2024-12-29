/*
  File: BlockType.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/26/2024
*/

#include "BlockType.h"

BlockType::BlockType(std::string textureName, ShaderType shaderType, bool emit)
    : top(textureName), bottom(textureName), north(textureName), east(textureName), south(textureName), west(textureName), shaderType(shaderType), emit(emit) {}

BlockType::BlockType(std::string textureY, std::string textureSides, ShaderType shaderType)
    : top(textureY), bottom(textureY), north(textureSides), east(textureSides), south(textureSides), west(textureSides), shaderType(shaderType) {}

BlockType::BlockType(std::string textureTop, std::string textureBottom, std::string textureSides, ShaderType shaderType)
    : top(textureTop), bottom(textureBottom), north(textureSides), east(textureSides), south(textureSides), west(textureSides), shaderType(shaderType) {}

BlockType::BlockType(std::string textureTop, std::string textureBottom, std::string textureNorth,
                     std::string textureEast, std::string textureSouth, std::string textureWest, ShaderType shaderType)
    : top(textureTop), bottom(textureBottom), north(textureNorth), east(textureEast), south(textureSouth), west(textureWest), shaderType(shaderType) {}

void BlockType::validate() const
{
  if (top.empty() || bottom.empty() || north.empty() || east.empty() || south.empty() || west.empty())
  {
    std::cerr << "BlockType validation failed: One or more textures are missing." << std::endl;
  }
}