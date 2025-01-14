#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
  Position = position;
  WorldUp = up;
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
  Position = glm::vec3(posX, posY, posZ);
  WorldUp = glm::vec3(upX, upY, upZ);
  Yaw = yaw;
  Pitch = pitch;
  updateCameraVectors();
}

void Camera::SetProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane)
{
  projectionMatrix = glm::mat4(1.0f);
  projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio /* (scr_width / scr_height) */, nearPlane, farPlane);
}

glm::mat4 Camera::GetViewMatrix()
{
  return BuildLookAtMatrix(Position, Position + Front, WorldUp);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
  if (projectionMatrix == glm::mat4(1.0f))
  {
    std::cerr << "Projection matrix not set!" << std::endl;
    return glm::mat4(1.0f);
  }
  return projectionMatrix;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
  float velocity = MovementSpeed * deltaTime;
  auto previousPosition = Position;

  if (direction == Camera_Movement::FORWARD)
    Position += Front * velocity;
  if (direction == Camera_Movement::BACKWARD)
    Position -= Front * velocity;
  if (direction == Camera_Movement::LEFT)
    Position -= Right * velocity;
  if (direction == Camera_Movement::RIGHT)
    Position += Right * velocity;

  if (!yFlying)
    Position.y = previousPosition.y;

  if (direction == Camera_Movement::UP)
    Position += Up * velocity;
  if (direction == Camera_Movement::DOWN)
    Position -= Up * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
  xOffset *= MouseSensitivity;
  yOffset *= MouseSensitivity;

  Yaw += xOffset;
  Pitch += yOffset;

  if (constrainPitch)
  {
    if (Pitch > 89.98f)
      Pitch = 89.98f;
    if (Pitch < -89.98)
      Pitch = -89.98f;
  }

  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float offset)
{
  Zoom += offset;

  if (Zoom < 0.2f)
    Zoom = 0.2f;
  if (Zoom > 45.0f)
    Zoom = 45.0f;
}

void Camera::setFlyY(bool value)
{
  yFlying = value;
}

void Camera::updateCameraVectors()
{
  glm::vec3 newFront;

  // calculate the new front using the math i could never reproduce like that
  newFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  newFront.y = sin(glm::radians(Pitch));
  newFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
  Front = glm::normalize(newFront);

  // re-calculate right and up
  // normalize them as their length would change with looking up/down y, affecting movement speed
  Right = glm::normalize(glm::cross(Front, WorldUp));
  Up = glm::normalize(glm::cross(Right, Front));
}

glm::mat4 Camera::BuildLookAtMatrix(glm::vec3 pos, glm::vec3 target, glm::vec3 worldUp)
{
  glm::vec3 z, y, x;

  // calculate the target vector
  z = glm::normalize(pos - target);

  // calculate the camera-local right vector (cross worldUp / z)
  x = glm::normalize(glm::cross(worldUp, z));

  // get the camera-local y as the cross product of the local z and x
  y = glm::cross(z, x); // no need to normalize, cross of two perpendicular unit vectors is always a unit vector

  // glm mat4 uses column-major order, so values have to entered column by column instead of row by row
  glm::mat4 rotation = glm::mat4(
      x.x, y.x, z.x, 0,
      x.y, y.y, z.y, 0,
      x.z, y.z, z.z, 0,
      0, 0, 0, 1);

  // glm mat4 uses column-major order, so values have to entered column by column instead of row by row
  glm::mat4 translation = glm::mat4(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      -pos.x, -pos.y, -pos.z, 1);

  return rotation * translation;
}