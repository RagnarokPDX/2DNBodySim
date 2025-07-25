#include "app.h"
#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {}
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {}

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

void App::run() {
  circle.centerX = 0;
  circle.centerY = 0;
  circle.radius = 0.5f;
  circle.resolution = 1024;

  auto pair = genereteCirleVerticiesAndIndicies(circle);
  printVector(pair.first);
  printVector(pair.second);

  glEnable(GL_DEPTH_TEST);
  Shader ourShader("/home/ragnarok/projects/opengl/nbody/res/vert.glsl",
                   "/home/ragnarok/projects/opengl/nbody/res/frag.glsl");

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, pair.first.size() * sizeof(float),
               &pair.first[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               pair.second.size() * sizeof(unsigned int), &pair.second[0],
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  ourShader.use();

  // TODO implemetn zoom;
  Camera camera(glm::vec3(0.0f, 0.0f, -1.0f));
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window, camera);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float aspect =
        static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT);
    float orthoHeight = 1.0f;
    float orthoWidth = orthoHeight * aspect;

    // glm::mat4 projection = glm::ortho(
    //     -static_cast<float>(SCR_WIDTH) / 2, static_cast<float>(SCR_WIDTH) /
    //     2, -static_cast<float>(SCR_WIDTH) / 2, static_cast<float>(SCR_WIDTH)
    //     / 2, 1.0f, 100.f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), camera.position);

    glm::mat4 projection = glm::ortho(-8.0f, 8.0f, // left, right
                                      -4.5f, 4.5f, // bottom, top
                                      -1.0f, 100.0f);
    // projection =
    //    glm::perspective(glm::radians(45.0f),
    //                    (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("model", model);
    ourShader.setMat4("view", view);

    ourShader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, circle.resolution * 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void App::shutdown() {
  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
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
