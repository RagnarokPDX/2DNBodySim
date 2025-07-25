#include "app.h"
#include "camera.h"
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

void App::run() {
  circle.centerX = 0;
  circle.centerY = 0;
  circle.radius = 0.5;
  circle.resolution = 3;

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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  ourShader.use();

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    float aspect = SCR_WIDTH / SCR_HEIGHT;
    float viewWidth = SCR_HEIGHT * aspect;

    // Create orthographic projection
    glm::mat4 projection =
        glm::ortho(-viewWidth / 2.0f, viewWidth / 2.0f,   // Left, Right
                   -viewHeight / 2.0f, viewHeight / 2.0f, // Bottom, Top
                   -1.0f, 1.0f                            // Near, Far
        );
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
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

void App::processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
