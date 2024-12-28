/*
  File: BlockRegistry.h
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/27/2024
*/

#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>

#include "BlockType.h"
#include "BlockMeshGenerator.h"

#include "renderer/texture/Texture.h"
#include "renderer/texture/TextureAtlas.h"
#include "renderer/shader/Shader.h"
#include "renderer/shader/ShaderProvider.h"
#include "renderer/render_entity/RenderEntity.h"

class BlockRegistry
{
public:
  static BlockRegistry &getInstance()
  {
    static BlockRegistry instance;
    return instance;
  }

  BlockRegistry(const BlockRegistry &) = delete;
  BlockRegistry &operator=(const BlockRegistry &) = delete;

  void registerBlock(const std::string &blockId, const BlockType &blockType);

  RenderEntity &getBlockRenderEntity(const std::string &id);
  const RenderEntity &getBlockRenderEntity(const std::string &id) const;

  bool hasBlock(const std::string &blockId) const;

private:
  BlockRegistry();
  ~BlockRegistry() = default;

  std::unordered_map<std::string, std::unique_ptr<RenderEntity>> blocks;

  Shader shader;
  TextureAtlas textureAtlas;
  Texture atlasTexture;
  BlockMeshGenerator meshGenerator;
};