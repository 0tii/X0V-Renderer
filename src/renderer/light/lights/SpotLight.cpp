/*
  File: SpotLight.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/6/2025
*/

#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 diffuse)
    : position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), diffuse(diffuse)
{
}