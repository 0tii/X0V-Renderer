#pragma once

#include <vector>
#include <iostream>
#include <glad/glad.h>

#include "renderer/material/Material.h"
#include "renderer/material/DefaultMaterial.hpp"
#include "renderer/mesh/VertexAttribute.h"
#include "renderer/Renderer.h"

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

  void bind() const;
  void unbind() const;
  void draw(Renderer &renderer, const glm::mat4 modelMatrix) const;
  void drawWireframe(Renderer &renderer, const glm::mat4 modelMatrix) const;

  // setters
  void setMaterial(Material *material);

private:
  Material *material;

  std::vector<float> vertices;
  std::vector<int> indices;
  std::vector<VertexAttribute> vertexAttributes;
  unsigned int VBO = 0, VAO = 0, EBO = 0;

  void setupMesh();
  void free();
};