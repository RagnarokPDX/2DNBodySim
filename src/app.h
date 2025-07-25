#ifndef APP_H
#define APP_H
#include "camera.h"
#include "shader.h"

#include "util.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/glad.h>
class App {
public:
  App();

  int init();
  void run();
  void shutdown();

private:
  GLFWwindow *window;
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  float deltaTime;
  float lastFrame;
  // expand this out to array of shaders for expendability later

  // hack but works for now just have one resoluiton sized circle
  Circle circle;
  void processInput(GLFWwindow *window, Camera &camera);
};

#endif
