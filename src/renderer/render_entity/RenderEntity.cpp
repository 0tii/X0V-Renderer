/*
  File: RenderEntity.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/23/2024
*/

#include "RenderEntity.h"

size_t RenderEntity::nextId = 0;

RenderEntity::RenderEntity(Mesh *mesh, Material *mat)
    : transform(), mesh(mesh), material(mat), id(nextId++)
{
}

RenderEntity::~RenderEntity()
{
}

void RenderEntity::setMesh(Mesh *mesh)
{
  this->mesh = mesh;
}

void RenderEntity::setMaterial(Material *material)
{
  this->material = material;
}

Transform &RenderEntity::getTransform()
{
  return transform;
}

const Transform &RenderEntity::getTransform() const
{
  return transform;
}

Mesh *RenderEntity::getMesh()
{
  return mesh;
}

Material *RenderEntity::getMaterial()
{
  return material;
}

size_t RenderEntity::getId() const
{
  return id;
}
