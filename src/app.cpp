#include "app.h"
#include <glad/glad.h>
#include <iostream>

#define SCR_WIDTH 800;
#define SCR_HEIGHT 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {}
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {}

int App::init() {
  window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // tell GLFW to capture our mouse
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  return 1;
}

void App::run() {}

void App::shutdown() {}
