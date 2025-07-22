#ifndef APP_H
#define APP_H
#include "shader.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class App {
public:
  App();

  int init();
  void run();
  void shutdown();

private:
  GLFWwindow *window;

  // expand this out to array of shaders for expendability later
  Shader shader;
};
#endif
