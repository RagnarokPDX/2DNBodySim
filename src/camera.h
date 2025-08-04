#ifndef CAMERA_H
#define CAMERA_H

#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Constants for Camera, maybe throw into config file later on
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float SPEED = 25.0f;
const float ZOOM = 45.0f;
// orhtograpic camera
//
enum Camera_Movment { UP, DOWN, LEFT, RIGHT };

class Camera {

public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 right;
  glm::vec3 up;

  float MovementSpeed;
  float Zoom;
  float MouseSensitivity;

  // remeber y direction is up in opengl space
  Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f))
      : MovementSpeed(SPEED), Zoom(ZOOM) {
    position = pos;
    right = glm::vec3(1.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0, 1.0, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
  };

  void processKeyboard(Camera_Movment direction, float deltaTime) {
    float vel = MovementSpeed * deltaTime;

    switch (direction) {
    case UP:
      position += up * vel;
      break;
    case DOWN:
      position -= up * vel;
      break;
    case LEFT:
      position -= right * vel;
      break;
    case RIGHT:
      position += right * vel;
      break;
    }
  }

  void ProcessMouseScroll(float yoffset) {
    Zoom -= (float)yoffset * 0.5; // apply dampening
    if (Zoom < 1.0f)
      Zoom = 1.0f;
    if (Zoom > 100.0f)
      Zoom = 100.0f;
  }

  glm::mat4 GetViewMatrix() {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position));
  }
};

#endif // !
