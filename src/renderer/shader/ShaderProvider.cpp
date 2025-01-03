/*
  File: ShaderProvider.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/28/2024
*/

#include "ShaderProvider.h"

ShaderProvider::ShaderProvider()
{
  addShader(ShaderType::Block, "../assets/shaders/block-shader.vert", "../assets/shaders/block-shader-2.0.frag");
  addShader(ShaderType::LightBlock, "../assets/shaders/block-shader.vert", "../assets/shaders/light-source-shader.frag");
  addShader(ShaderType::LightReceiver, "../assets/shaders/block-shader.vert", "../assets/shaders/light-receiver-shader.frag");
}

Shader &ShaderProvider::getShader(ShaderType type)
{
  auto result = this->shaders.find(type);

  if (result != shaders.end())
    return result->second;
  else
  {
    std::cout << "[ShaderProvider] Key '" << type << "' does not have a shader associated in the registry." << std::endl;
    throw std::runtime_error("No shader registered for key.");
  }
}

void ShaderProvider::addShader(ShaderType type, const char *vertPath, const char *fragPath)
{
  if (!hasShader(type))
  {
    Shader shader(vertPath, fragPath);

    std::cout << "[ShaderProvider] Registering Shader " << type << " with  id " << shader.ID << std::endl;

    shaders.emplace(type, std::move(shader));
  }
  else
    std::cout << "[ShaderProvider] Key '" << type << "' already exists in shaders. Skipping adding." << std::endl;
}

bool ShaderProvider::hasShader(ShaderType type)
{
  return shaders.find(type) != shaders.end();
}
