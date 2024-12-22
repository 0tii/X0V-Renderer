/*
  File: Renderer.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/22/2024
*/

#pragma once

#include <iostream>
#include <vector>

#include "renderer/camera/Camera.h"
#include "renderer/shader/Shader.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  void addCamera(Camera *camera);
  void removeCamera(Camera *camera);

  // --- debug ---
  void listCameras() const;

  // --- setters ---
  void setActiveCamera(Camera *camera);
  void setActiveCamera(size_t index);

  // --- getters ---
  Camera *getActiveCamera() const;
  size_t getCameraCount() const;

  void setCameraUniforms(const Shader &shader) const;

private:
  Camera *activeCamera = nullptr;
  std::vector<Camera *> cameras;
};