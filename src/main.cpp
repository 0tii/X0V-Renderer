#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/shader/Shader.h"
#include "renderer/camera/Camera.h"
#include "renderer/window/window.h"
#include "renderer/texture/Texture.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, float *textureBlendFactor);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

unsigned int setupQuadFromTriangles();
unsigned int setupCube();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = .0f;
float lastFrame = .0f;

float lastMouseX = 400.0f;
float lastMouseY = 300.0f;
bool initialMouseEnter = true;

Camera camera = Camera(glm::vec3(0, 0, 3));

float pitch, yaw;
float fov = 45.0f;

int main()
{
  GLWindow window = GLWindow();
  window.create("LearnOpenGL", SCR_WIDTH, SCR_HEIGHT);
  window.setViewPort(SCR_WIDTH, SCR_HEIGHT);
  window.setMouseAccelleration(false);

  window.setFramebufferSizeCallback(framebuffer_size_callback);
  window.setMouseMoveCallback(mouse_callback);
  window.setScrollCallback(scroll_callback);

  // create textures
  Texture crateTexture = Texture("../resources/textures/container.jpg", GL_RGB);
  Texture smileyTexture = Texture("../resources/textures/awesomeface.png", GL_RGBA);

  // create our shader
  Shader ourShader("../resources/shaders/shader.vert", "../resources/shaders/shader.frag");

  float textureBlendFactor = 0.2f;

  ourShader.use();
  ourShader.setInt("texture1", 0);
  ourShader.setInt("texture2", 1);

  unsigned int VAO = setupCube();

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)};

  while (!window.shouldClose())
  {
    processInput(window.getWindow(), &textureBlendFactor);

    glEnable(GL_BLEND); // enable blending function to allow for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enables depth testing, openGL will keep a depth buffer (z-buffer) to keep track of what to render on top of what
    // it allows rendering one thing in front of another and hiding the back object
    glEnable(GL_DEPTH_TEST);

    // rendering logic...
    glClearColor(.4f, .0f, .6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    crateTexture.bind(0);
    smileyTexture.bind(1);

    glBindVertexArray(VAO); // Bind the VAO before drawing

    ourShader.use();
    ourShader.setFloat("blendFactor", textureBlendFactor);

    // create a perspective projection matrix  -- this kind of translates everything to screen coords
    glm::mat4 projection = glm::mat4(1.0f);
    // FOV              // width / height                     //near//far plane
    projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    ourShader.setMat4("view", camera.GetViewMatrix());
    ourShader.setMat4("projection", projection);

    // comment in for wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // draw from EBO
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    for (unsigned int i = 0; i < 10; i++)
    {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 25.0f * (i + 1);
      if (i % 3 == 0)
        angle *= (float)glfwGetTime();
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      ourShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // comment in to disable wireframe again after drawing
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // unbind the VAO
    glBindVertexArray(0);

    window.swapBuffers();
    window.pollEvents();

    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
  }

  return 0;
}

unsigned int setupCube()
{
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  unsigned int VAO, VBO;

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // DO NOT FORGET THE OFFSET!!
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return VAO;
}

unsigned int setupQuadFromTriangles()
{
  //------------------- declare vertices

  float vertices[] = {
      // positions          // colors           // texture coords
      0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
  };

  unsigned int indices[] = {
      0, 1, 3,
      1, 2, 3};

  //--------------- create vertex buffer and vertex array and entity buffer
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO); // generate a vertex array object VAO
  glGenBuffers(1, &VBO);      // generate a vertex buffer object VBO
  glGenBuffers(1, &EBO);      // generate entity buffer object

  glBindVertexArray(VAO); // first bind the VAO

  glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        // we bind the VBO so the VAO can record it
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // we send the buffer data to the GPU

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);                                      // bind the EBO so VAO can record it
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // send the EBO data to the GPU

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // we tell the VAO how to interpret the position vertices
  glEnableVertexAttribArray(0);                                                  // we enable the position attribute (layout location 0)

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // we tell the VAO how to interpret our color values from the vertices array
  glEnableVertexAttribArray(1);                                                                    // we enable the color attribute (layout location 1)

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float))); // its the 2nd value, 2 floats long, 8 floats to the next value, starting after the 6th float
  glEnableVertexAttribArray(2);                                                                    // enable the layout attrbiute "location 2" in the vertex shader

  glBindBuffer(GL_ARRAY_BUFFER, 0); // we unbind the VBO as we dont need it anymore

  return VAO;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, float *textureBlendFactor)
{
  const float cameraSpeed = 2.5f * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    *textureBlendFactor = std::min(1.0f, *textureBlendFactor + 0.05f);
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    *textureBlendFactor = std::max(0.0f, *textureBlendFactor - 0.05f);

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