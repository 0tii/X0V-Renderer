/*
  File: BlockMeshGenerator.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/26/2024
*/

#include "BlockMeshGenerator.h"

uMeshPtr BlockMeshGenerator::generateBlockMesh(const BlockType &type, const TextureAtlas &atlas)
{
  glm::vec4 topUV = atlas.getUVRegion(type.top);
  glm::vec4 bottomUV = atlas.getUVRegion(type.bottom);
  glm::vec4 northUV = atlas.getUVRegion(type.north);
  glm::vec4 eastUV = atlas.getUVRegion(type.east);
  glm::vec4 southUV = atlas.getUVRegion(type.south);
  glm::vec4 westUV = atlas.getUVRegion(type.west);

  auto frontFace = generateCubeFace(
      glm::vec3(-0.5f, -0.5f, -0.5f),
      glm::vec3(0.5f, -0.5f, -0.5f),
      glm::vec3(-0.5f, 0.5f, -0.5f),
      glm::vec3(0.5f, 0.5f, -0.5f),
      southUV,
      glm::vec3(0, 0, -1));

  auto backFace = generateCubeFace(
      glm::vec3(0.5f, -0.5f, 0.5f),
      glm::vec3(-0.5f, -0.5f, 0.5f),
      glm::vec3(0.5f, 0.5f, 0.5f),
      glm::vec3(-0.5f, 0.5f, 0.5f),
      northUV,
      glm::vec3(0, 0, 1));

  auto leftFace = generateCubeFace(
      glm::vec3(-0.5f, -0.5f, 0.5f),
      glm::vec3(-0.5f, -0.5f, -0.5f),
      glm::vec3(-0.5f, 0.5f, 0.5f),
      glm::vec3(-0.5f, 0.5f, -0.5f),
      westUV,
      glm::vec3(-1, 0, 0));

  auto rightFace = generateCubeFace(
      glm::vec3(0.5f, -0.5f, -0.5f),
      glm::vec3(0.5f, -0.5f, 0.5f),
      glm::vec3(0.5f, 0.5f, -0.5f),
      glm::vec3(0.5f, 0.5f, 0.5f),
      eastUV,
      glm::vec3(1, 0, 0));

  auto topFace = generateCubeFace(
      glm::vec3(-0.5f, 0.5f, -0.5f),
      glm::vec3(0.5f, 0.5f, -0.5f),
      glm::vec3(-0.5f, 0.5f, 0.5f),
      glm::vec3(0.5f, 0.5f, 0.5f),
      topUV,
      glm::vec3(0, 1, 0));

  auto bottomFace = generateCubeFace(
      glm::vec3(-0.5f, -0.5f, 0.5f),
      glm::vec3(0.5f, -0.5f, 0.5f),
      glm::vec3(-0.5f, -0.5f, -0.5f),
      glm::vec3(0.5f, -0.5f, -0.5f),
      bottomUV,
      glm::vec3(0, -1, 0));

  std::vector<float> vertices;
  vertices.insert(vertices.end(), topFace.begin(), topFace.end());
  vertices.insert(vertices.end(), frontFace.begin(), frontFace.end());
  vertices.insert(vertices.end(), backFace.begin(), backFace.end());
  vertices.insert(vertices.end(), rightFace.begin(), rightFace.end());
  vertices.insert(vertices.end(), leftFace.begin(), leftFace.end());
  vertices.insert(vertices.end(), bottomFace.begin(), bottomFace.end());

  std::vector<VertexAttribute>
      vertexAttributes = {
          VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0),                 // position data
          VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float)), // texcoord data
          VertexAttribute(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 5 * sizeof(float)), // normal data
      };

  return std::make_unique<Mesh>(vertices.data(), vertices.size(), vertexAttributes);
}

std::vector<float> BlockMeshGenerator::generateCubeFace(
    glm::vec3 bottomLeft,
    glm::vec3 bottomRight,
    glm::vec3 topLeft,
    glm::vec3 topRight,
    glm::vec4 uvRegion,
    glm::vec3 normals)
{
  return {
      bottomLeft.x, bottomLeft.y, bottomLeft.z, uvRegion.x, uvRegion.w, normals.x, normals.y, normals.z,    // bottom-left
      bottomRight.x, bottomRight.y, bottomRight.z, uvRegion.z, uvRegion.w, normals.x, normals.y, normals.z, // bottom-right
      topRight.x, topRight.y, topRight.z, uvRegion.z, uvRegion.y, normals.x, normals.y, normals.z,          // top-right
      topRight.x, topRight.y, topRight.z, uvRegion.z, uvRegion.y, normals.x, normals.y, normals.z,          // top-right
      topLeft.x, topLeft.y, topLeft.z, uvRegion.x, uvRegion.y, normals.x, normals.y, normals.z,             // top-left
      bottomLeft.x, bottomLeft.y, bottomLeft.z, uvRegion.x, uvRegion.w, normals.x, normals.y, normals.z     // bottom-left
  };
}

uMeshPtr BlockMeshGenerator::generatePlainBlockMeshWithNormals()
{
  std::vector<float> vertices{
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

      -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

  std::vector<VertexAttribute>
      vertexAttributes = {
          VertexAttribute(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0),                 // position data
          VertexAttribute(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float)), // normals
      };

  return std::make_unique<Mesh>(vertices.data(), vertices.size(), vertexAttributes);
}