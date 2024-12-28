#include "Shader.h"

unsigned int Shader::currentlyActiveShaderProgramId = 0;

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
  std::string vertexShaderCode;
  std::string fragmentShaderCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    std::stringstream vShaderStream, fShaderStream;

    // read the file buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // close file handlers
    vShaderFile.close();
    fShaderFile.close();

    // convert the streams to strings
    vertexShaderCode = vShaderStream.str();
    fragmentShaderCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << "VertexShader Path: " << vertexPath << "FragmentShader Path: " << fragmentPath << std::endl;
  }

  const char *vShaderCode = vertexShaderCode.c_str();
  const char *fShaderCode = fragmentShaderCode.c_str();

  unsigned int vertexShaderId = compileVertexShader(vShaderCode);
  unsigned int fragmentShaderId = compileFragmentShader(fShaderCode);

  ID = glCreateProgram();
  glAttachShader(ID, vertexShaderId);
  glAttachShader(ID, fragmentShaderId);
  glLinkProgram(ID);

  // print linking errors if any
  int success;
  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertexShaderId);
  glDeleteShader(fragmentShaderId);
}

void Shader::use()
{
  if (currentlyActiveShaderProgramId != ID)
  {
    glUseProgram(ID);
    currentlyActiveShaderProgramId = ID;
#ifdef DEBUG
    std::cout << "Activating shader " << ID << " through ex- or implicit Shader::use()" << std::endl;
#endif
  }
}

/// <summary>
/// set a boolean uniform value on the shader program
/// </summary>
/// <param name="name">the name of the uniform attribute</param>
/// <param name="value">the value to set the uniform to</param>
void Shader::setBool(const std::string &name, bool value)
{
  use();
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

/// <summary>
/// set an integer uniform value on the shader program
/// </summary>
/// <param name="name">the name of the uniform attribute</param>
/// <param name="value">the value to set the uniform to</param>
void Shader::setInt(const std::string &name, int value)
{
  use();
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

/// <summary>
/// set a float uniform value on the shader program
/// </summary>
/// <param name="name">the name of the uniform attribute</param>
/// <param name="value">the value to set the uniform to</param>
void Shader::setFloat(const std::string &name, float value)
{
  use();
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value)
{
  use();
  glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y)
{
  use();
  glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value)
{
  use();
  glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
  use();
  glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value)
{
  use();
  glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
  use();
  glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat)
{
  use();
  glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat)
{
  use();
  glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
  use();
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::compileVertexShader(const char *code)
{
  unsigned int vertexShaderId;
  int success;
  char infoLog[512];

  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &code, NULL);
  glCompileShader(vertexShaderId);

  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  };

  return vertexShaderId;
}

unsigned int Shader::compileFragmentShader(const char *code)
{
  unsigned int fragmentShaderId;
  int success;
  char infoLog[512];

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &code, NULL);
  glCompileShader(fragmentShaderId);

  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  };

  return fragmentShaderId;
}