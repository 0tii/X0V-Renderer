/*
  File: LightManager.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/9/2025
*/

#pragma once

#include <span>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "renderer/light/lights/DirectionalLight.h"
#include "renderer/render_entity/RenderEntity.h"
#include "renderer/light/lights/PointLight.h"
#include "renderer/light/lights/SpotLight.h"
#include "renderer/light/LightData.h"

class LightManager
{
public:
  LightManager();

  void updateUBO();

  void addDirectionalLight(const DirectionalLight &light);
  void addPointLight(const PointLight &light);
  void addSpotLight(const SpotLight &light);

  void updatePointLight(size_t index, const PointLight &light);
  void updateDirectionalLight(size_t index, const DirectionalLight &light);
  void updateSpotLight(size_t index, const SpotLight &light);

  std::span<const DirectionalLight> getDirectionalLights() const;
  std::span<const PointLight> getPointLights() const;
  std::span<const SpotLight> getSpotLights() const;

  std::vector<int> getApplicableDirLights(const RenderEntity &entity) const;
  std::vector<int> getApplicablePointLights(const RenderEntity &entity) const;
  std::vector<int> getApplicableSpotLights(const RenderEntity &entity) const;

  void recalculateAllPointLightRadii();

private:
  unsigned int lightUBO;

  std::vector<DirectionalLight> directionalLights;
  std::vector<PointLight> pointLights;
  std::vector<SpotLight> spotLights;

  std::vector<float> pointLightInfluenceRadii;

  void initializeUBO();
  float getPointLightSphereOfInfluence(const PointLight &light, float threshold = .01f) const;

  bool pointLightAffectsEntity(size_t index, const RenderEntity &entity) const;
  bool spotLightAffectsEntity(size_t, const RenderEntity &entity) const;
};