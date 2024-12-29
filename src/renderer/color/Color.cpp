/*
  File: Color.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/29/2024
*/

#include "Color.h"

#include <algorithm>

Color::Color(float rgb)
{
  this->r = rgb;
  this->g = rgb;
  this->b = rgb;
  this->a = 1;
}

Color::Color(float r, float g, float b)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = 1;
}

Color::Color(float r, float g, float b, float a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

glm::vec3 Color::toVec3() const
{
  return glm::vec3(r, g, b);
}

glm::vec4 Color::toVec4() const
{
  return glm::vec4(r, g, b, a);
}

Color &Color::darken(float amount)
{
  r = std::max(r - amount, 0.0f);
  g = std::max(g - amount, 0.0f);
  b = std::max(b - amount, 0.0f);

  return *this;
}

Color &Color::lighten(float amount)
{
  r = std::min(r + amount, 1.0f);
  g = std::min(g + amount, 1.0f);
  b = std::min(b + amount, 1.0f);

  return *this;
}

Color &Color::alpha(float alpha)
{
  a = std::min(std::max(alpha, 0.0f), 1.0f);
  return *this;
}

const Color Color::red = Color(1, 0, 0);
const Color Color::blue = Color(0, 0, 1);
const Color Color::green = Color(0, 1, 0);
const Color Color::cyan = Color(0, 1, 1);
const Color Color::orange = Color(1, .5f, 0);
const Color Color::yellow = Color(1, 1, 0);
const Color Color::lime = Color(.5f, 1, 0);
const Color Color::white = Color(1, 1, 1);
const Color Color::black = Color(0, 0, 0);
