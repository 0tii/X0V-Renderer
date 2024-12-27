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
#include "renderer/render_entity/RenderEntity.h"

class BlockRegistry
{
public:
  BlockRegistry(TextureAtlas &atlas, Shader &shader);
  ~BlockRegistry() = default;

  void registerBlock(const std::string &blockId, const BlockType &blockType);

  RenderEntity &getBlockRenderEntity(const std::string &id);
  const RenderEntity &getBlockRenderEntity(const std::string &id) const;

  bool hasBlock(const std::string &blockId) const;

private:
  std::unordered_map<std::string, std::unique_ptr<RenderEntity>> blocks;

  TextureAtlas &textureAtlas;
  Shader &shader;

  Texture atlasTexture;
  BlockMeshGenerator meshGenerator;
};