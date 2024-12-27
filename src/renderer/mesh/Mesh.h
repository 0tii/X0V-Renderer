#pragma once

#include <vector>
#include <iostream>
#include <glad/glad.h>

#include "renderer/material/Material.h"
#include "renderer/material/DefaultMaterial.hpp"
#include "renderer/mesh/VertexAttribute.h"

class Mesh
{
public:
  Mesh(const float *vertices, const size_t verticesCount, const std::vector<VertexAttribute> &vertexAttributes, const int *indices = nullptr, const size_t indicesCount = 0);
  Mesh(const std::vector<float> &vertices, const std::vector<VertexAttribute> &vertexAttributes, const std::vector<int> &indices = {});
  ~Mesh();

  // delete copy constructor and assignment operator
  Mesh(const Mesh &other) = delete;
  Mesh &operator=(const Mesh &other) = delete;

  // implement our copy and assign logic
  Mesh(Mesh &&other) noexcept;
  Mesh &operator=(Mesh &&other) noexcept;

  void bindBuffers() const;
  void unbindBuffers() const;
  void draw() const;

  int getVertexCount() const;
  int getIndexCount() const;

private:
  std::vector<float> vertices;
  std::vector<int> indices;
  std::vector<VertexAttribute> vertexAttributes;
  unsigned int VBO = 0, VAO = 0, EBO = 0;

  void setupMesh();
  void free();
};

using uMeshPtr = std::unique_ptr<Mesh>;
using sMeshPtr = std::shared_ptr<Mesh>;