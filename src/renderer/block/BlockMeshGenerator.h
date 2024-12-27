/*
  File: BlockMeshGenerator.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/26/2024
*/

#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "renderer/mesh/Mesh.h"
#include "renderer/block/BlockType.h"
#include "renderer/texture/TextureAtlas.h"

typedef std::unique_ptr<Mesh> uMeshPtr;

class BlockMeshGenerator
{
public:
  BlockMeshGenerator() = default;
  uMeshPtr generateBlockMesh(const BlockType &type, const TextureAtlas &atlas);

private:
  std::vector<float> generateCubeFace(
      glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight, glm::vec4 uvRegion);
};