/*
  File: BlockRegistry.cpp
  Author: Daniel H. Rauhut (0ti)
  GitHub: https://github.com/0tii
  Created: 12/27/2024
*/

#include "BlockRegistry.h"

BlockRegistry::BlockRegistry()
    : textureAtlas(
          std::unordered_map<std::string, std::string>{
              {"block_diamond_ore", "../assets/textures/block_diamond_ore.png"},
              {"block_sand", "../assets/textures/block_sand.png"},
              {"block_dirt", "../assets/textures/block_dirt.png"},
              {"block_grass_top", "../assets/textures/block_grass_top.png"},
              {"block_grass_side", "../assets/textures/block_grass_side.png"},
              {"block_stone", "../assets/textures/block_stone.png"},
              {"block_lamp", "../assets/textures/block_lamp_on.png"},
              {"block_oak_log_side", "../assets/textures/block_oak_log.png"},
              {"block_oak_log_top", "../assets/textures/block_oak_log_top.png"},
          },
          16),
      atlasTexture(textureAtlas.getTextureID())
{
  registerBlock("x0v_block_grass", BlockType("block_grass_top", "block_dirt", "block_grass_side"));
  registerBlock("x0v_block_oak_log", BlockType("block_oak_log_top", "block_oak_log_side"));
  registerBlock("x0v_block_dirt", BlockType("block_dirt"));
  registerBlock("x0v_block_diamond_ore", BlockType("block_diamond_ore"));
  registerBlock("x0v_block_sand", BlockType("block_sand"));
  registerBlock("x0v_block_stone", BlockType("block_stone"));
  registerBlock("x0v_block_lamp", BlockType("block_lamp", ShaderType::LightBlock));
}

void BlockRegistry::registerBlock(const std::string &blockId, const BlockType &blockType)
{
  std::cout << "[BlockRegistry] Registering block " << blockId << std::endl;

  auto blockMesh = meshGenerator.generateBlockMesh(blockType, textureAtlas);
  auto &providedShader = ShaderProvider::getInstance().getShader(blockType.shaderType); // yes this little shit here cost me 2 hours
  auto blockMaterial = std::make_unique<Material>(providedShader, atlasTexture);
  auto entity = std::make_unique<RenderEntity>(std::move(blockMesh), std::move(blockMaterial));

  blocks[blockId] = std::move(entity);
}

RenderEntity &BlockRegistry::getBlockRenderEntity(const std::string &id)
{
  auto result = blocks.find(id);

  if (result != blocks.end())
  {
    return *(result->second); // dereferene unique ptr to ref
  }

  std::cerr << "[Error] Could not find block with id " << id << " in the BlockRegistry" << std::endl;
  throw std::runtime_error("Block not found");
}

const RenderEntity &BlockRegistry::getBlockRenderEntity(const std::string &id) const
{
  auto result = blocks.find(id);

  if (result != blocks.end())
  {
    return *(result->second); // dereferene unique ptr to ref
  }

  std::cerr << "[Error] Could not find block with id " << id << " in the BlockRegistry" << std::endl;
  throw std::runtime_error("Block not found");
}

bool BlockRegistry::hasBlock(const std::string &blockId) const
{
  return blocks.find(blockId) != blocks.end();
}
