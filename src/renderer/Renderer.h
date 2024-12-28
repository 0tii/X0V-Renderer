/*
  File: Renderer.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/22/2024
*/

#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "renderer/camera/Camera.h"
#include "renderer/shader/Shader.h"
#include "renderer/render_entity/RenderEntity.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void initFrame(glm::vec3 color = {{(.03f)}, {(.7f)}, {(.91f)}} /*light blue*/) const;

  void addCamera(Camera *camera);
  void removeCamera(Camera *camera);

  void renderEntity(RenderEntity &entity) const;
  void renderEntity(RenderEntity *entity) const;

  // --- debug ---
  void listCameras() const;

  // --- setters ---
  void setActiveCamera(Camera *camera);
  void setActiveCamera(size_t index);

  void setWireframeRendering(bool enabled = true);

  // --- getters ---
  Camera *getActiveCamera() const;
  size_t getCameraCount() const;

  void setCameraUniforms(Shader &shader) const;

private:
  Camera *activeCamera = nullptr;
  std::vector<Camera *> cameras;
};