/*
  File: Color.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/29/2024
*/

#pragma once

#include <glm/glm.hpp>

struct Color
{
public:
  Color(float rgb);
  Color(float r, float g, float b);
  Color(float r, float g, float b, float a);

  float r, g, b, a;

  operator glm::vec3() const { return glm::vec3(r, g, b); }
  operator glm::vec4() const { return glm::vec4(r, g, b, a); }

  void darken(float amount);
  void lighten(float amount);

  static const Color red;
  static const Color blue;
  static const Color green;
  static const Color cyan;
  static const Color orange;
  static const Color yellow;
  static const Color lime;
  static const Color white;
  static const Color black;
};
