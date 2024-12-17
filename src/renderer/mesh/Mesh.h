#pragma once

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include "VertexAttribute.h"

class Mesh
{
public:
  Mesh(const float *vertices, const size_t verticesCount, const std::vector<VertexAttribute> &vertexAttributes, const int *indices = nullptr, const size_t indicesCount = 0);
  Mesh(const std::vector<float> &vertices, const std::vector<VertexAttribute> &vertexAttributes, const std::vector<int> &indices = {});
  ~Mesh();

  // delete copy constructor and assignment operator
  Mesh(const Mesh &other) = delete;
  Mesh &operator=(const Mesh &other) = delete;

  // implement our own logic
  Mesh(Mesh &&other) noexcept;
  Mesh &operator=(Mesh &&other) noexcept;

  void bind() const;
  void unbind() const;
  void draw() const;
  void drawWireframe() const;
  void free();

private:
  std::vector<float> vertices;
  std::vector<int> indices;
  std::vector<VertexAttribute> vertexAttributes;
  unsigned int VBO = 0, VAO = 0, EBO = 0;

  void setupMesh();
};