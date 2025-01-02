#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW = -90.0f;
const float PITCH = -16.0f;
const float SPEED = 6.0f;
const float SENSITIVITY = 0.065f;
const float ZOOM = 45.0f;

enum class Camera_Movement
{
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Camera
{
public:
  // camera Attributes
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  // euler Angles
  float Yaw;
  float Pitch;

  // camera options
  float MovementSpeed;
  float MouseSensitivity;
  float Zoom;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

  void ProcessKeyboard(Camera_Movement direction, float deltaTime);
  void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yOffset);
  void setFlyY(bool value);

  void SetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);

  glm::mat4 GetViewMatrix();
  glm::mat4 GetProjectionMatrix() const;

private:
  glm::mat4 projectionMatrix = glm::mat4(1.0f);
  void updateCameraVectors();
  glm::mat4 BuildLookAtMatrix(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp);

  bool yFlying = false;
};