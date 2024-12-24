/*
  File: Transform.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/23/2024
*/

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

class Transform
{

public:
  Transform();

  void setPosition(const glm::vec3 &pos);
  void setRotation(const glm::vec3 &rot);
  void setScale(const glm::vec3 &scl);

  glm::vec3 getPosition() const;
  glm::vec3 getRotation() const;
  glm::vec3 getScale() const;

  glm::mat4 getModelMatrix();

private:
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  // rotation in euler angles (x, y, z)
  glm::vec3 rotation{0.0f, 0.0f, 0.0f};
  glm::vec3 scale{1.0f, 1.0f, 1.0f};

  glm::quat rotationQuaternion;
  glm::mat4 modelMatrixCache;

  bool dirty = true;

  Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);

  void updateRotationQuaternion();
  void updateModelMatrix();
};