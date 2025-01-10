/*
  File: Scene.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/7/2025
*/

#pragma once

#include <vector>
#include <span>

#include "renderer/render_entity/RenderEntity.h"
#include "renderer/light/lights/DirectionalLight.h"
#include "renderer/light/lights/SpotLight.h"
#include "renderer/light/lights/PointLight.h"
#include "renderer/light/LightManager.h"

class Scene
{
public:
  Scene() = default;

  void addEntity(uRenderEntityPtr entity);

  std::span<const uRenderEntityPtr> getEntities() const;
  LightManager *getLightManager();

private:
  std::vector<uRenderEntityPtr> renderEntities;

  LightManager lightManager = LightManager();
};