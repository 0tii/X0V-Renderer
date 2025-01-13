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

void LightManager::updateUBO(Camera &activeCamera)
{
    glm::mat4 viewMatrix = activeCamera.GetViewMatrix();

    LightData lightData;
    lightData.numDirectionalLights = directionalLights.size();
    lightData.numPointLights = pointLights.size();
    lightData.numSpotLights = spotLights.size();

    auto transformVector = [&](const glm::vec3 &vec, float w)
    {
        return glm::vec3(viewMatrix * glm::vec4(vec, w));
    };

    for (size_t i = 0; i < directionalLights.size(); ++i)
    {
        lightData.directionalLights[i].direction = transformVector(directionalLights[i].direction, 0.0f);
        lightData.directionalLights[i].ambient = directionalLights[i].ambient;
        lightData.directionalLights[i].diffuse = directionalLights[i].diffuse;
        lightData.directionalLights[i].specular = directionalLights[i].specular;
    }

    // Transform point lights
    for (size_t i = 0; i < pointLights.size(); ++i)
    {
        lightData.pointLights[i].position = transformVector(pointLights[i].position, 1.0f);
        lightData.pointLights[i].ambient = pointLights[i].ambient;
        lightData.pointLights[i].diffuse = pointLights[i].diffuse;
        lightData.pointLights[i].specular = pointLights[i].specular;
        lightData.pointLights[i].constant = pointLights[i].constant;
        lightData.pointLights[i].linear = pointLights[i].linear;
        lightData.pointLights[i].quadratic = pointLights[i].quadratic;
    }

    // Transform spotlights
    for (size_t i = 0; i < spotLights.size(); ++i)
    {
        lightData.spotLights[i].position = transformVector(spotLights[i].position, 1.0f);
        lightData.spotLights[i].direction = transformVector(spotLights[i].direction, 0.0f);
        lightData.spotLights[i].cutOff = spotLights[i].cutOff;
        lightData.spotLights[i].outerCutOff = spotLights[i].outerCutOff;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData), &lightData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    LightData debugData;
    glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
    glGetBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightData), &debugData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
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
