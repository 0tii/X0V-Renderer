#pragma once

#include <iostream>
#include <filesystem>

#include "renderer/material/Material.h"
#include "renderer/shader/Shader.h"
#include "renderer/texture/Texture.h"

class DefaultMaterial
{
public:
  static Material &getDefaultMaterial()
  {

    static Shader shader("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");
    static Texture texture("../resources/textures/default_texture.png", GL_RGBA);

    if (texture.getTextureId() == 0)
    {
      std::cerr << "Default texture failed to load!\n";
    }

    static Material defaultMaterial(shader, texture);

    return defaultMaterial;
  }
};