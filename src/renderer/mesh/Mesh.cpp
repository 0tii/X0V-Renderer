#include "Mesh.h"

Mesh::Mesh(const float *vertices, const size_t verticesCount, const std::vector<VertexAttribute> &vertexAttributes, const int *indices, const size_t indicesCount)
    : vertices(vertices, vertices + verticesCount),
      vertexAttributes(vertexAttributes)
{
  if (indices != nullptr)
  {
    this->indices = std::vector<int>(indices, indices + indicesCount);
  }

  setupMesh();
}

Mesh::Mesh(const std::vector<float> &vertices, const std::vector<VertexAttribute> &vertexAttributes, const std::vector<int> &indices)
    : vertices(vertices),
      indices(indices),
      vertexAttributes(vertexAttributes)
{
  setupMesh();
}

Mesh::~Mesh()
{
  free();
}

// Move Constructor: Transfer ownership
Mesh::Mesh(Mesh &&other) noexcept
    : VAO(other.VAO), VBO(other.VBO), EBO(other.EBO),
      vertices(std::move(other.vertices)), indices(std::move(other.indices)), vertexAttributes(std::move(other.vertexAttributes))
{
  other.VAO = other.VBO = other.EBO = 0;
}

// assignment operator for move
Mesh &Mesh::operator=(Mesh &&other) noexcept
{
  if (this != &other)
  {
    if (VAO)
      glDeleteVertexArrays(1, &VAO);
    if (VBO)
      glDeleteBuffers(1, &VBO);
    if (EBO)
      glDeleteBuffers(1, &EBO);

    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;

    // Invalidate the moved-from object
    other.VAO = other.VBO = other.EBO = 0;
  }
  return *this;
}

void Mesh::free()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  if (!indices.empty())
  {
    glDeleteBuffers(1, &EBO);
  }
}

void Mesh::bind() const
{
  glBindVertexArray(VAO);

  if (!indices.empty())
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  }
}

void Mesh::unbind() const
{
  glBindVertexArray(0);
  //? no need to unbind the EBO, as it is unbound when the VAO is unbound
}

void Mesh::draw() const
{
  this->bind();
  if (indices.empty())
  {
    int numVertices = vertices.size() / (vertexAttributes[0].stride / sizeof(float));
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
  }
  else
  {
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  }
  this->unbind();
}

void Mesh::drawWireframe() const
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  this->draw();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::setupMesh()
{
  if (vertexAttributes.empty())
  {
    std::cerr << "Error: No vertex attributes provided for the mesh!" << std::endl;
    return;
  }

  glGenVertexArrays(1, &this->VAO);
  glBindVertexArray(this->VAO);

  glGenBuffers(1, &this->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

  if (!indices.empty())
  {
    glGenBuffers(1, &this->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(int), this->indices.data(), GL_STATIC_DRAW);
  }

  // set the vertex attributes
  for (const auto &vA : this->vertexAttributes)
  {
    glVertexAttribPointer(vA.layoutIndex, vA.size, vA.type, vA.normalized, vA.stride, vA.offset);
    glEnableVertexAttribArray(vA.layoutIndex);
  }
}