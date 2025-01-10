/*
  File: LightManager.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 1/9/2025
*/

#include "LightManager.h"

#include <numeric>

LightManager::LightManager()
{
    initializeUBO();
}

void LightManager::updateUBO()
{
    LightData lightData;
    lightData.numDirectionalLights = directionalLights.size();
    lightData.numPointLights = pointLights.size();
    lightData.numSpotLights = spotLights.size();

    std::copy(directionalLights.begin(), directionalLights.end(), lightData.directionalLights.data());
    std::copy(pointLights.begin(), pointLights.end(), lightData.pointLights.data());
    std::copy(spotLights.begin(), spotLights.end(), lightData.spotLights.data());

    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData), &lightData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    LightData debugData;
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glGetBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData), &debugData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Print values to confirm correctness.
    std::cout << "Num Dir Lights: " << debugData.numDirectionalLights << std::endl;
    std::cout << "First Dir Light Direction: " << debugData.directionalLights[0].direction.x << std::endl;
}

void LightManager::addDirectionalLight(const DirectionalLight &light)
{
    this->directionalLights.push_back(light);
}

void LightManager::addPointLight(const PointLight &light)
{
    this->pointLights.push_back(light);
    this->pointLightInfluenceRadii.push_back(getPointLightSphereOfInfluence(light));
}

void LightManager::addSpotLight(const SpotLight &light)
{
    this->spotLights.push_back(light);
}

void LightManager::updatePointLight(size_t index, const PointLight &light)
{
    if (index >= pointLights.size())
    {
        throw std::out_of_range("Invalid index for PointLight update");
    }

    pointLights[index] = light;
    pointLightInfluenceRadii[index] = getPointLightSphereOfInfluence(light);
}

void LightManager::updateDirectionalLight(size_t index, const DirectionalLight &light)
{
    if (index >= pointLights.size())
    {
        throw std::out_of_range("Invalid index for PointLight update");
    }

    directionalLights[index] = light;
}

void LightManager::updateSpotLight(size_t index, const SpotLight &light)
{
    if (index >= pointLights.size())
    {
        throw std::out_of_range("Invalid index for PointLight update");
    }

    spotLights[index] = light;
}

void LightManager::recalculateAllPointLightRadii()
{
    pointLightInfluenceRadii.clear();
    pointLightInfluenceRadii.reserve(pointLights.size());
    for (const auto &light : pointLights)
    {
        pointLightInfluenceRadii.push_back(getPointLightSphereOfInfluence(light));
    }
}

std::span<const DirectionalLight> LightManager::getDirectionalLights() const
{
    return std::span<const DirectionalLight>(this->directionalLights.data(), this->directionalLights.size());
}

std::span<const PointLight> LightManager::getPointLights() const
{
    return std::span<const PointLight>(this->pointLights.data(), this->pointLights.size());
}

std::span<const SpotLight> LightManager::getSpotLights() const
{
    return std::span<const SpotLight>(this->spotLights.data(), this->spotLights.size());
}

std::vector<int> LightManager::getApplicableDirLights(const RenderEntity &entity) const
{
    std::vector<int> indices(directionalLights.size());
    std::iota(indices.begin(), indices.end(), 0);
    return indices;
}

std::vector<int> LightManager::getApplicablePointLights(const RenderEntity &entity) const
{
    std::vector<int> applicableLights;

    for (size_t i = 0; i < pointLights.size(); ++i)
    {
        if (pointLightAffectsEntity(i, entity))
        {
            applicableLights.push_back(static_cast<int>(i));
        }
    }

    return applicableLights;
}

std::vector<int> LightManager::getApplicableSpotLights(const RenderEntity &entity) const
{
    // TODO: return only applicable spot lights
    std::vector<int> indices(spotLights.size());
    std::iota(indices.begin(), indices.end(), 0);
    return indices;
}

// ------- private ------- //

void LightManager::initializeUBO()
{
    glGenBuffers(1, &lightUBO);
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightData), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightUBO);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    std::cout << "Size of DirectionalLight: " << sizeof(DirectionalLight) << " bytes\n";
    std::cout << "Size of PointLight: " << sizeof(PointLight) << " bytes\n";
    std::cout << "Size of SpotLight: " << sizeof(SpotLight) << " bytes\n";
    std::cout << "Size of LightData: " << sizeof(LightData) << " bytes\n";

    std::cout << "Size of LightData: " << sizeof(LightData) << " bytes" << std::endl;
}

float LightManager::getPointLightSphereOfInfluence(const PointLight &light, float threshold) const
{
    float C = light.constant - (1.0f / threshold);
    float B = light.linear;
    float A = light.quadratic;

    float discriminant = B * B - 4 * A * C;

    if (discriminant < 0)
    {
        return std::numeric_limits<float>::max();
    }

    float d = (-B + std::sqrt(discriminant)) / (2 * A);
    return d;
}

bool LightManager::pointLightAffectsEntity(size_t index, const RenderEntity &entity) const
{
    float pointLightRadius = pointLightInfluenceRadii[index];

    auto lightPosition = pointLights[index].position;
    auto entityPosition = entity.getTransform().getPosition();

    float distance = glm::distance(lightPosition, entityPosition);

    return distance <= pointLightRadius;
}

bool LightManager::spotLightAffectsEntity(size_t nice, const RenderEntity &entity) const
{
    // TODO: implement spotlight culling
    // cache cone values and update when spotlights get updates
    // check if the entity intersects with the area of effect from its transform
    return false;
}
