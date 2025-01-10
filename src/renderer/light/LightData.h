/*
  File: LightData.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/9/2025
*/

#define MAX_DIRECTIONAL_LIGHTS 32
#define MAX_POINT_LIGHTS 512
#define MAX_SPOT_LIGHTS 256

#pragma once

#include <array>

#include "renderer/light/lights/DirectionalLight.h"
#include "renderer/light/lights/PointLight.h"
#include "renderer/light/lights/SpotLight.h"

struct LightData
{
public:
  LightData() = default;

  std::array<DirectionalLight, MAX_DIRECTIONAL_LIGHTS> directionalLights;
  std::array<PointLight, MAX_POINT_LIGHTS> pointLights;
  std::array<SpotLight, MAX_SPOT_LIGHTS> spotLights;

  int numDirectionalLights, numPointLights, numSpotLights, padding;
};