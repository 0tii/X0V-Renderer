/*
  File: Transform.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/23/2024
*/

#include "Transform.h"

Transform::Transform()
{
  updateRotationQuaternion();
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
    : position(pos), rotation(rot), scale(scl)
{
  updateRotationQuaternion();
}

glm::mat4 Transform::getModelMatrix()
{
  if (dirty)
  {
    updateModelMatrix();
    dirty = false;
  }
  return modelMatrixCache;
}

void Transform::updateRotationQuaternion()
{
  rotationQuaternion = glm::quat(glm::radians(rotation));
}

void Transform::updateModelMatrix()
{
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model *= glm::mat4(rotationQuaternion);
  model = glm::scale(model, scale);
  modelMatrixCache = model;
}

void Transform::setPosition(const glm::vec3 &pos)
{
  position = pos;
  dirty = true;
}

void Transform::setRotation(const glm::vec3 &rot)
{
  rotation = rot;
  updateRotationQuaternion();
  dirty = true;
}

void Transform::setScale(const glm::vec3 &scl)
{
  scale = scl;
  dirty = true;
}

glm::vec3 Transform::getPosition() const
{
  return position;
}

glm::vec3 Transform::getRotation() const
{
  return rotation;
}

glm::vec3 Transform::getScale() const
{
  return scale;
}