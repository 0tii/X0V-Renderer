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

    static Shader shader("../assets/shaders/block-shader.vert", "../assets/shaders/block-shader.frag");
    static Texture texture("../resources/textures/default_texture.png", GL_RGBA);

    texture.setWrappingMode(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

    if (texture.getTextureId() == 0)
    {
      std::cerr << "Default texture failed to load!\n";
    }

    static Material defaultMaterial(shader, texture);

    return defaultMaterial;
  }
};