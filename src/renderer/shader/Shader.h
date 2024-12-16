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

	Shader(const char* vertexPath, const char* fragmentPath);

	void use(); // use/activate the shader

	// --- utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;

	/// <summary>
	/// set a float uniform value on the shader program
	/// </summary>
	/// <param name="name">the name of the uniform attribute</param>
	/// <param name="value">the value to set the uniform to</param>
	void setFloat(const std::string& name, float value) const;

	void setMat2(const std::string& name, const glm::mat2& value) const;
	void setMat3(const std::string& name, const glm::mat3& value) const;
	void setMat4(const std::string& name, const glm::mat4& value) const;

	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;

	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;

protected:
	unsigned int compileVertexShader(const char* shaderCode);
	unsigned int compileFragmentShader(const char* shaderCode);
};