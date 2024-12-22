/*
  File: Renderer.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/22/2024
*/

#pragma once

#include <iostream>

#include "renderer/camera/Camera.h"
#include "renderer/shader/Shader.h"

class Renderer
{
public:
  Renderer();
  ~Renderer();

  // --- setters ---
  void setCamera(Camera *camera);
  void applyCameraTransforms(const Shader &shader) const;

private:
  Camera *activeCamera;
};