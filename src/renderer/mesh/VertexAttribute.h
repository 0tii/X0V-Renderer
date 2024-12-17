#pragma once

#include <glad/glad.h>

struct VertexAttribute
{
  VertexAttribute(GLuint layoutIdx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, size_t offset)
      : layoutIndex(layoutIdx), size(size), type(type), normalized(normalized), stride(stride), offset((void *)offset) {};
  // the layout index in the shader
  GLuint layoutIndex;
  // number of components / array members
  GLint size;
  // the data type of the members
  GLenum type;
  // whether the data should be normalized
  GLboolean normalized;
  // the byte offset between consecutive generic vertex attributes
  GLsizei stride;
  // the offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target
  const void *offset;
};
