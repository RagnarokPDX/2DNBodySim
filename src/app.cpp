#include "app.h"
#include "camera.h"
#include "shader.h"
#include "simulation.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, -1.0f));
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

App::App() {
  EBO = 0;
  VBO = 0;
  VAO = 0;
  window = NULL;
  deltaTime = 0;
  lastFrame = 0;
}

int App::init() {

  if (!glfwInit())
    return -1;

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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  camera.Zoom = 1.0f;
  return 1;
}

void App::run() {

  Simulation sim;
  sim.generateRandomPositions(5);
  std::vector<glm::vec2> positions = sim.getPositions();

  circle.centerX = 0;
  circle.centerY = 0;
  circle.radius = 0.5f;
  circle.resolution = 4;

  auto pair = genereteCirleVerticiesAndIndicies(circle);

  glEnable(GL_DEPTH_TEST);
  Shader ourShader("/home/ragnarok/projects/opengl/nbody/res/vert.glsl",
                   "/home/ragnarok/projects/opengl/nbody/res/frag.glsl");

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &positionVBO);

  glBindVertexArray(VAO);
  // circle data
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, pair.first.size() * sizeof(float),
               &pair.first[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

  // instance data
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
               &positions[0], GL_DYNAMIC_DRAW);

  glVertexAttribDivisor(1, 1);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

  // indicieis
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               pair.second.size() * sizeof(unsigned int), &pair.second[0],
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  ourShader.use();
  int height;
  int width;

  sim.printPositions();
  std::cout << positions.size();
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwGetWindowSize(window, &width, &height);

    processInput(window, camera);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float aspect =
        static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT);
    float orthoHeight = 1.0f;
    float orthoWidth = orthoHeight * aspect;

    glm::mat4 view = glm::translate(glm::mat4(1.0f), camera.position);

    glm::mat4 projection = glm::ortho(
        -static_cast<float>(width) / 2 * camera.Zoom / 100,
        static_cast<float>(width) / 2 * camera.Zoom / 100, // left, right
        -static_cast<float>(height) / 2 * camera.Zoom / 100,
        static_cast<float>(height) / 2 * camera.Zoom / 100, // bottom, top
        -1.0f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("model", model);
    ourShader.setMat4("view", view);

    ourShader.use();
    glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, circle.resolution * 3, GL_UNSIGNED_INT, 0);
    glDrawElementsInstanced(GL_TRIANGLES, circle.resolution * 3,
                            GL_UNSIGNED_INT, 0, positions.size());

    // glDrawElements(GL_TRIANGLES, circle.resolution * 3, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void App::shutdown() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
}

void App::processInput(GLFWwindow *window, Camera &camera) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(UP, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(DOWN, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(RIGHT, deltaTime);
}
