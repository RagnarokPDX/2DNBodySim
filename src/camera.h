#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Constants for Camera, maybe throw into config file later on
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// orhtograpic camera

class Camera {

public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
};

#endif // !
