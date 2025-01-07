/*
  File: PointLight.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/6/2025
*/

#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

struct PointLight
{
  PointLight(glm::vec3 position, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular, float constant, float linear, float quadratic);

  glm::vec3 position, diffuse, ambient, specular;
  float constant, linear, quadratic;
};