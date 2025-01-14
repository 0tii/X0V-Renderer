/*
  File: Scene.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/7/2025
*/

#include "Scene.h"

void Scene::addEntity(uRenderEntityPtr entity)
{
    this->renderEntities.push_back(std::move(entity));
}

std::span<const uRenderEntityPtr> Scene::getEntities() const
{
    return std::span<const uRenderEntityPtr>(this->renderEntities.data(), this->renderEntities.size());
}

LightManager *Scene::getLightManager()
{
    return &this->lightManager;
}