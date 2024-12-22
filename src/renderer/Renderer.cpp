/*
  File: Renderer.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/22/2024
*/

#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::setCamera(Camera *camera)
{
  this->activeCamera = camera;
}

void Renderer::applyCameraTransforms(const Shader &shader) const
{
  if (!activeCamera)
  {
    std::cerr << "No active camera set!" << std::endl;
  }

  shader.setMat4("view", activeCamera->GetViewMatrix());
  shader.setMat4("projection", activeCamera->GetProjectionMatrix());
}
