#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>

#include "renderer/camera/Camera.h"
#include "renderer/window/window.h"
#include "renderer/Renderer.h"
#include "renderer/render_entity/RenderEntity.h"
#include "renderer/block/BlockRegistry.h"
#include "renderer/shader/ShaderProvider.h"
#include "renderer/color/Color.h"
#include "renderer/scene/Scene.h"
#include "renderer/light/lights/PointLight.h"
#include "renderer/light/lights/DirectionalLight.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

float deltaTime = .0f;
float lastFrame = .0f;

float lastMouseX = SCR_WIDTH / 2;
float lastMouseY = SCR_HEIGHT / 2;
bool initialMouseEnter = true;

Camera camera = Camera(glm::vec3(0, 0, 8));
Renderer renderer = Renderer();

float fov = 45.0f;

int main()
{
  GLWindow window = GLWindow();
  window.create("Voxel Schmoxel", SCR_WIDTH, SCR_HEIGHT);
  window.setViewPort(SCR_WIDTH, SCR_HEIGHT);
  window.setMouseAccelleration(false);

  window.setFramebufferSizeCallback(framebuffer_size_callback);
  window.setMouseMoveCallback(mouse_callback);
  window.setScrollCallback(scroll_callback);

  // set up camera for renderer
  camera.SetProjectionMatrix(fov, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
  renderer.setActiveCamera(&camera);

  // init blockregistry
  BlockRegistry &blockRegistry = BlockRegistry::getInstance();

  glm::vec3 cubePositions[] = {
      glm::vec3(-1.0f, -5.0f, -1.0f),
      glm::vec3(0.0f, -5.0f, -1.0f),
      glm::vec3(1.0f, -5.0f, -1.0f),
      glm::vec3(2.0f, -5.0f, -1.0f),
      glm::vec3(-1.0f, -5.0f, 0.0f),
      glm::vec3(0.0f, -5.0f, 0.0f),
      glm::vec3(1.0f, -5.0f, 0.0f),
      glm::vec3(2.0f, -5.0f, 0.0f),
      glm::vec3(-1.0f, -5.0f, 1.0f),
      glm::vec3(0.0f, -5.0f, 1.0f),
      glm::vec3(1.0f, -5.0f, 1.0f),
      glm::vec3(2.0f, -5.0f, 1.0f),
      glm::vec3(-1.0f, -5.0f, 2.0f),
      glm::vec3(0.0f, -5.0f, 2.0f),
      glm::vec3(1.0f, -5.0f, 2.0f),
      glm::vec3(2.0f, -5.0f, 2.0f)};

  while (!window.shouldClose())
  {
    processInput(window.getWindow());

    renderer.initFrame(glm::vec3(0));
    Scene testScene = Scene();

    // add directional light
    auto dirLightDir = glm::normalize(glm::vec3(camera.GetViewMatrix() * glm::vec4(0.3f, -1.0f, 0.2f, 0.0f)));
    DirectionalLight dirLight = DirectionalLight(dirLightDir, glm::vec3(.4f), glm::vec3(.7f));
    testScene.getLightManager()->addDirectionalLight(dirLight);

    // add point light
    auto pointLightPosition = camera.GetViewMatrix() * glm::vec4(glm::vec3(-2.0f, -3.0f, -2.0f), 1.0f);
    PointLight pl = PointLight(pointLightPosition, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(.1f), glm::vec3(.7f), 1.0f, 0.09f, 0.032f);
    testScene.getLightManager()->addPointLight(pl);

    std::unique_ptr<RenderEntity> lampEntity2 = blockRegistry.createBlock("x0v_block_lamp", BlockType("block_lamp", ShaderType::LightBlock));
    lampEntity2->getTransform().setPosition(glm::vec3(-2.0f, -3.0f, -2.0f));
    lampEntity2->getMaterial()->getShader().setVec3("lightColor", glm::vec3(0.0f, 0.0f, 1.0f));
    lampEntity2->getTransform().setScale(glm::vec3(0.4f));

    testScene.addEntity(std::move(lampEntity2));

    // add point light 2
    auto pointLightPosition2 = camera.GetViewMatrix() * glm::vec4(glm::vec3(2.0f, -3.0f, 2.0f), 1.0f);
    PointLight pl2 = PointLight(pointLightPosition, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(.1f), glm::vec3(.7f), 1.0f, 0.09f, 0.032f);
    testScene.getLightManager()->addPointLight(pl2);

    std::unique_ptr<RenderEntity> lampEntity = blockRegistry.createBlock("x0v_block_lamp", BlockType("block_lamp", ShaderType::LightBlock));
    lampEntity->getTransform().setPosition(glm::vec3(2.0f, -3.0f, 2.0f));
    lampEntity->getMaterial()->getShader().setVec3("lightColor", glm::vec3(1.0f, 0.0f, 0.0f));
    lampEntity->getTransform().setScale(glm::vec3(0.4f));

    testScene.addEntity(std::move(lampEntity));

    for (unsigned int i = 0; i < (sizeof(cubePositions) / sizeof(cubePositions[0])); i++)
    {
      std::unique_ptr<RenderEntity> renderBlock;

      switch (i % 5)
      {
      case 0:
        renderBlock = blockRegistry.createBlock("x0v_block_grass", BlockType("block_grass_top", "block_dirt", "block_grass_side"));
        break;
      case 1:
        renderBlock = blockRegistry.createBlock("x0v_block_dirt", BlockType("block_dirt"));
        break;
      case 2:
        renderBlock = blockRegistry.createBlock("x0v_block_diamond_ore", BlockType("block_diamond_ore", ShaderType::Surface, true));
        break;
      case 3:
        renderBlock = blockRegistry.createBlock("x0v_block_sand", BlockType("block_sand"));
        break;
      case 4:
        renderBlock = blockRegistry.createBlock("x0v_block_stone", BlockType("block_stone"));
        break;
      }

      renderBlock->getTransform().setPosition(cubePositions[i]);

      testScene.addEntity(std::move(renderBlock));
    }

    auto oakLog = blockRegistry.createBlock("x0v_block_oak_log", BlockType("block_oak_log_top", "block_oak_log_side"));
    oakLog->getTransform().setPosition(glm::vec3(0.0f, -4.0f, 0.0f));
    testScene.addEntity(std::move(oakLog));

    oakLog = blockRegistry.createBlock("x0v_block_oak_log", BlockType("block_oak_log_top", "block_oak_log_side"));
    oakLog->getTransform().setPosition(glm::vec3(0.0f, -3.0f, 0.0f));
    testScene.addEntity(std::move(oakLog));

    renderer.renderScene(&testScene);

    window.swapBuffers();
    window.pollEvents();

    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
  }

  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  const float cameraSpeed = 3.5f * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
}

void mouse_callback(GLFWwindow *window, double xPosIn, double yPosIn)
{
  float xPos = static_cast<float>(xPosIn);
  float yPos = static_cast<float>(yPosIn);

  if (initialMouseEnter)
  {
    lastMouseX = xPos;
    lastMouseY = yPos;
    initialMouseEnter = false;
  }

  float xOffset = xPos - lastMouseX;
  float yOffset = lastMouseY - yPos;

  lastMouseX = xPos;
  lastMouseY = yPos;

  camera.ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}