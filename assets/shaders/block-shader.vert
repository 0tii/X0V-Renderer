#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal; //normal vector perpendicular to block face

out vec2 TexCoord;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  FragPos = vec3(model * vec4(aPos, 1.0)); // fragment position in world space
  TexCoord = aTexCoord;

  // convert the normals to world space using inverse transposed model matrix
  // we can not use the normal model matrix since its a 4x4 and our normals are vec3
  // this operation (inverse) is costly, so this is usually done on the CPU and sent as a uniform
  Normal = mat3(transpose(inverse(model))) * aNormal; 
};