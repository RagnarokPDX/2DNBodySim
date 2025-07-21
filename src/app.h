#ifndef APP_H
#define APP_H
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
};
#endif
