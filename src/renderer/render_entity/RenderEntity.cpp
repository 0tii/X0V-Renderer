/*
  File: RenderEntity.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/23/2024
*/

#include "RenderEntity.h"

size_t RenderEntity::nextId = 0;

RenderEntity::RenderEntity(uMeshPtr mesh, uMaterialPtr mat)
    : transform(), mesh(std::move(mesh)), material(std::move(mat)), id(nextId++)
{
}

RenderEntity::~RenderEntity()
{
}

void RenderEntity::setMesh(uMeshPtr mesh)
{
  this->mesh = std::move(mesh);
}

void RenderEntity::setMaterial(uMaterialPtr material)
{
  this->material = std::move(material);
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
  return mesh.get();
}

Material *RenderEntity::getMaterial()
{
  return material.get();
}

size_t RenderEntity::getId() const
{
  return id;
}
