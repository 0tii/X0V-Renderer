#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/shader/Shader.h"
#include "renderer/camera/Camera.h"
#include "renderer/window/window.h"
#include "renderer/Renderer.h"
#include "renderer/render_entity/RenderEntity.h"
#include "renderer/block/BlockRegistry.h"

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

Camera camera = Camera(glm::vec3(0, 0, 3));
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

  RenderEntity *cubeEntities[] = {
      &blockRegistry.getBlockRenderEntity("x0v_block_dirt"),
      &blockRegistry.getBlockRenderEntity("x0v_block_diamond_ore"),
      &blockRegistry.getBlockRenderEntity("x0v_block_sand"),
      &blockRegistry.getBlockRenderEntity("x0v_block_grass"),
      &blockRegistry.getBlockRenderEntity("x0v_block_stone"),
  };

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

    renderer.initFrame();

    for (unsigned int i = 0; i < (sizeof(cubePositions) / sizeof(cubePositions[0])); i++)
    {
      cubeEntities[i % 5]->getTransform().setPosition(cubePositions[i]);

      renderer.renderEntity(cubeEntities[i % 5]);
    }

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
  const float cameraSpeed = 2.5f * deltaTime;

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