#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/camera/Camera.h"
#include "renderer/window/window.h"
#include "renderer/Renderer.h"
#include "renderer/render_entity/RenderEntity.h"
#include "renderer/block/BlockRegistry.h"
#include "renderer/shader/ShaderProvider.h"

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

  RenderEntity *cubeEntities[] = {
      &blockRegistry.getBlockRenderEntity("x0v_block_dirt"),
      &blockRegistry.getBlockRenderEntity("x0v_block_diamond_ore"),
      &blockRegistry.getBlockRenderEntity("x0v_block_sand"),
      &blockRegistry.getBlockRenderEntity("x0v_block_grass"),
      &blockRegistry.getBlockRenderEntity("x0v_block_stone"),
  };

  RenderEntity *lamp = &blockRegistry.getBlockRenderEntity("x0v_block_lamp");

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

  bool moveLight = false;
  glm::vec3 lightPos(-3.0f, -2.5f, 1.0f);

  while (!window.shouldClose())
  {
    processInput(window.getWindow());

    renderer.initFrame();

    if (moveLight)
    {
      float time = glfwGetTime();
      lightPos.x = sin(time * 0.5f) * 2.0f;
      lightPos.z = cos(time * 0.5f) * 2.0f;
    }

    // set shader uniforms
    ShaderProvider::getInstance().getShader(ShaderType::Block).use();
    ShaderProvider::getInstance().getShader(ShaderType::Block).setVec3("lightPos", lightPos);
    ShaderProvider::getInstance().getShader(ShaderType::Block).setVec3("viewPos", camera.Position);

    for (unsigned int i = 0; i < (sizeof(cubePositions) / sizeof(cubePositions[0])); i++)
    {
      // enable wireframe for every 2nd block
      // renderer.setWireframeRendering((i % 3 == 0));

      cubeEntities[i % 5]->getTransform().setPosition(cubePositions[i]);

      renderer.renderEntity(cubeEntities[i % 5]);
    }

    lamp->getTransform().setPosition(lightPos);
    lamp->getTransform().setScale(glm::vec3(0.4f));
    renderer.renderEntity(lamp);

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