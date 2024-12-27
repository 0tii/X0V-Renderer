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

void Renderer::initFrame(glm::vec3 color) const
{
  glEnable(GL_BLEND); // enable blending function to allow for transparency
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enables depth testing, openGL will keep a depth buffer (z-buffer) to keep track of what to render on top of what
  // it allows rendering one thing in front of another and hiding the back object
  glEnable(GL_DEPTH_TEST);

  glClearColor(color.x, color.y, color.z, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::addCamera(Camera *camera)
{
  cameras.push_back(camera);
  if (!activeCamera)
  {
    activeCamera = camera;
  }
}

void Renderer::removeCamera(Camera *camera)
{
  if (activeCamera == camera)
  {
    std::cout << "[Warning] Removing active camera!" << std::endl;
    activeCamera = nullptr;
  }

  cameras.erase(std::remove(cameras.begin(), cameras.end(), camera), cameras.end());
}

void Renderer::renderEntity(RenderEntity &entity) const
{
  if (!activeCamera)
  {
    std::cerr << "No active camera set!" << std::endl;
  }

  Shader shader = entity.getMaterial()->getShader();
  shader.use();

  setCameraUniforms(shader);

  shader.setMat4("model", entity.getTransform().getModelMatrix());

  entity.getMaterial()->bind();
  entity.getMesh()->bindBuffers();

  entity.getMesh()->draw();

  entity.getMesh()->unbindBuffers();
  entity.getMaterial()->unbind();
}

void Renderer::renderEntity(RenderEntity *entity) const
{
  this->renderEntity(*entity);
}

void Renderer::setActiveCamera(Camera *camera)
{
  this->activeCamera = camera;
}

void Renderer::setActiveCamera(size_t index)
{
  if (index < cameras.size())
  {
    activeCamera = cameras[index];
  }
  else
  {
    std::cerr << "Camera index out of range!" << std::endl;
  }
}

Camera *Renderer::getActiveCamera() const
{
  return activeCamera;
}

size_t Renderer::getCameraCount() const
{
  return cameras.size();
}

/// @brief Set Camera uniforms on a shader program
/// @param shader The shader to set the camera transform uniforms on
void Renderer::setCameraUniforms(const Shader &shader) const
{
  if (!activeCamera)
  {
    std::cerr << "No active camera set!" << std::endl;
  }

  shader.setMat4("view", activeCamera->GetViewMatrix());
  shader.setMat4("projection", activeCamera->GetProjectionMatrix());
}

void Renderer::listCameras() const
{
  std::cout << "Cameras in Renderer:" << std::endl;
  for (size_t i = 0; i < cameras.size(); ++i)
  {
    std::cout << i << ": Camera at " << cameras[i] << std::endl;
  }
}