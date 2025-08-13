#ifndef APP_H
#define APP_H
#include "camera.h"
#include "shader.h"
#include <glm/fwd.hpp>
#include <vector>
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
  static Camera camera;

  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;
  unsigned int positionVBO;
  float deltaTime;
  float lastFrame;
  int scr_width;
  int scr_height;

  void processInput(GLFWwindow *window, Camera &camera);
  void setupRun(std::vector<glm::vec2> &positions);

  void render(Shader &shader, std::vector<glm::vec2> &positions);

  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
  static void scroll_callback(GLFWwindow *window, double xoffset,
                              double yoffset);
};
#endif
