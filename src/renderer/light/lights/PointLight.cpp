/*
  File: PointLight.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/6/2025
*/

#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular, float constant, float linear, float quadratic)
    : position(position), diffuse(diffuse), ambient(ambient), specular(specular), constant(constant), linear(linear), quadratic(quadratic), padding(quadratic)
{
}