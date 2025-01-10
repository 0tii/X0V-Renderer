/*
  File: SpotLight.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/6/2025
*/

#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

struct SpotLight
{
  SpotLight() = default;
  SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 diffuse = glm::vec3(.7f));

  glm::vec3 position, direction, diffuse;
  float cutOff, outerCutOff;
};