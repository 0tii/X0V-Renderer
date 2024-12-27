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
  RenderEntity(uMeshPtr mesh, uMaterialPtr mat);
  ~RenderEntity();

  void setMesh(uMeshPtr mesh);
  void setMaterial(uMaterialPtr material);

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

  uMeshPtr mesh;
  uMaterialPtr material;
};

using uRenderEntityPtr = std::unique_ptr<RenderEntity>;
using sRenderEntityPtr = std::shared_ptr<RenderEntity>;
