/*
  File: RenderEntity.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/23/2024
*/

#pragma once

#include "renderer/mesh/Mesh.h"
#include "renderer/material/Material.h"
#include "renderer/transform/Transform.h"

class RenderEntity
{
public:
  RenderEntity(Mesh *mesh, Material *mat);
  ~RenderEntity();

  void setMesh(Mesh *mesh);
  void setMaterial(Material *material);

  size_t getId() const;

  Transform &getTransform();
  const Transform &getTransform() const; // read only access

  Mesh *getMesh();
  Material *getMaterial();

private:
  // TODO: Solid method for unique IDs
  static size_t nextId;
  size_t id;

  Transform transform;

  Mesh *mesh;
  Material *material;
};