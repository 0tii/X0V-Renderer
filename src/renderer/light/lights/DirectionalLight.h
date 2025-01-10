/*
  File: DirectionalLight.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/6/2025
*/

#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

struct DirectionalLight
{
public:
  DirectionalLight() = default;
  DirectionalLight(glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient = glm::vec3(0.2f));

  glm::vec3 direction, diffuse, specular, ambient;
};