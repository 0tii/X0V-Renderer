#pragma once

#include <glad/glad.h> // include glad before any other gl headers
#include <GLFW/glfw3.h>
#include <iostream>

class GLWindow
{
public:
  GLWindow();
  ~GLWindow();

  GLFWwindow *create(const char *title, unsigned int width, unsigned int height);

  // properties
  bool shouldClose();
  void swapBuffers();
  void pollEvents();

  // setters
  void setViewPort(unsigned int width, unsigned int height);
  void setMouseAccelleration(bool enabled);
  void setFramebufferSizeCallback(void (*callback)(GLFWwindow *, int, int));
  void setMouseMoveCallback(void (*callback)(GLFWwindow *, double, double));
  void setScrollCallback(void (*callback)(GLFWwindow *, double, double));

  // getters
  double getTime();
  GLFWwindow *getWindow();

private:
  GLFWwindow *window;
};