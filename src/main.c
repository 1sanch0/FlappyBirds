#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "flappybirds.h"

#define WIDTH 500
#define HEIGHT 900
#define TITLE "Flappy Birds in C and OpenGL!"
#define RESIZABLE GLFW_FALSE

bool pressedKeys[350] = {false};

void framebuffer_size_callback(GLFWwindow *w, int width, int height);
void key_callback(GLFWwindow *w, int key, int scancode, int action, int mods);

int main(void) {
  GLFWwindow *window;

  // GLFW WINDOW INITIALIZATION
  // --------------------------

  // glfw: initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, RESIZABLE);

  // glfw window creation
  window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window");
    exit(1);
  }

  glfwMakeContextCurrent(window);

  // Callbacks:
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetKeyCallback(window, key_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD");
    exit(1);
  }

  glfwSwapInterval(1); // V-sync

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // MAIN LOOP
  // --------------------------
  double t0, t1, dt;
  t0 = glfwGetTime();

  FB fb = {};
  FB_init(&fb, WIDTH, HEIGHT);

  while (!glfwWindowShouldClose(window)) {
    // Delta time
    t1 = glfwGetTime();
    dt = t1 - t0;
    t0 = t1;

    // Update
    FB_update(&fb, pressedKeys, dt);

    // Render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    FB_draw(&fb);

    // Swap buffers and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  FB_destroy(&fb);

  // DESTROY WINDOW
  // --------------------------
  glfwDestroyWindow(window);
  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *w, int width, int height) {
  glViewport(0, 0, width, height); (void)w;
}

void key_callback(GLFWwindow *w, int key, int scancode, int action, int mods) {
  (void)w;(void)scancode;(void)mods;
  if (action == GLFW_PRESS)
    pressedKeys[key] = true;
  else if (action == GLFW_RELEASE)
    pressedKeys[key] = false;
}
