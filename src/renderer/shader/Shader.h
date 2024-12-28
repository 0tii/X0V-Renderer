#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>

class Shader
{
public:
  unsigned int ID; // shader program id

  Shader(const char *vertexPath, const char *fragmentPath);

  void use(); // use/activate the shader

  // --- utility uniform functions
  void setBool(const std::string &name, bool value);
  void setInt(const std::string &name, int value);

  /// <summary>
  /// set a float uniform value on the shader program
  /// </summary>
  /// <param name="name">the name of the uniform attribute</param>
  /// <param name="value">the value to set the uniform to</param>
  void setFloat(const std::string &name, float value);

  void setMat2(const std::string &name, const glm::mat2 &value);
  void setMat3(const std::string &name, const glm::mat3 &value);
  void setMat4(const std::string &name, const glm::mat4 &value);

  void setVec2(const std::string &name, const glm::vec2 &value);
  void setVec2(const std::string &name, float x, float y);

  void setVec3(const std::string &name, const glm::vec3 &value);
  void setVec3(const std::string &name, float x, float y, float z);

  void setVec4(const std::string &name, const glm::vec4 &value);
  void setVec4(const std::string &name, float x, float y, float z, float w);

protected:
  unsigned int compileVertexShader(const char *shaderCode);
  unsigned int compileFragmentShader(const char *shaderCode);

private:
  static unsigned int currentlyActiveShaderProgramId;
};

using uShaderPtr = std::unique_ptr<Shader>;
using sShaderPtr = std::shared_ptr<Shader>;