/*
  File: ShaderProvider.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/28/2024
*/

#pragma once

#include <unordered_map>

#include "renderer/shader/Shader.h"
#include "renderer/shader/ShaderType.h"

class ShaderProvider
{
public:
  static ShaderProvider &getInstance()
  {
    static ShaderProvider instance;
    return instance;
  }

  Shader &getShader(ShaderType type);
  void addShader(ShaderType type, const char *vertPath, const char *fragPath);
  bool hasShader(ShaderType type);

private:
  ShaderProvider();
  std::unordered_map<ShaderType, Shader> shaders;
};