/*
  File: BlockType.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/26/2024
*/

#include "BlockType.h"

BlockType::BlockType(std::string textureName)
    : top(textureName), bottom(textureName), north(textureName), east(textureName), south(textureName), west(textureName) {}

BlockType::BlockType(std::string textureY, std::string textureSides)
    : top(textureY), bottom(textureY), north(textureSides), east(textureSides), south(textureSides), west(textureSides) {}

BlockType::BlockType(std::string textureTop, std::string textureBottom, std::string textureSides)
    : top(textureTop), bottom(textureBottom), north(textureSides), east(textureSides), south(textureSides), west(textureSides) {}

BlockType::BlockType(std::string textureTop, std::string textureBottom, std::string textureNorth,
                     std::string textureEast, std::string textureSouth, std::string textureWest)
    : top(textureTop), bottom(textureBottom), north(textureNorth), east(textureEast), south(textureSouth), west(textureWest) {}

void BlockType::validate() const
{
  if (top.empty() || bottom.empty() || north.empty() || east.empty() || south.empty() || west.empty())
  {
    std::cerr << "BlockType validation failed: One or more textures are missing." << std::endl;
  }
}