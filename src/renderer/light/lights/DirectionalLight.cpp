/*
  File: DirectionalLight.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/6/2025
*/

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 ambient)
    : direction(direction), diffuse(diffuse), specular(specular), ambient(ambient)
{
}