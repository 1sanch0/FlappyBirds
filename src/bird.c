#include "bird.h"
#include <math.h>
#include "settings.h"

typedef struct {
  GLfloat position[2];
  GLfloat uv[2];
} __attribute__((packed)) Vertex;

void bird_init(Bird *bird, Mat4 *proj, float y) {
  bird->y = y;
  bird->acc = 0;
  bird->theta = 0;
  // Flap animation
  bird->t = 0;
  bird->flapSpeed = 10;
  // Bird model matrix
  identity(&bird->model);

  // Bird dimentions: width x height = 34 x 24
  float ar = 24.0f / 34.0f;

  Vertex vertices[] = {
    {{ 0.5f, ar/2.0f}, {1.0f, 1.0f}}, // Top right
    {{ 0.5f,-ar/2.0f}, {1.0f, 0.0f}}, // Bottom right
    {{-0.5f,-ar/2.0f}, {0.0f, 0.0f}}, // Bottom left
    {{-0.5f, ar/2.0f}, {0.0f, 1.0f}}, // Top left
  };

  GLuint indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };

  glGenVertexArrays(1, &bird->VAO);
  glBindVertexArray(bird->VAO);

  glGenBuffers(1, &bird->VBO);

  glBindBuffer(GL_ARRAY_BUFFER, bird->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  // UV attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(1);

  glGenBuffers(1, &bird->EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bird->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);

  bird->shader = createShader("./assets/shaders/bird.vert", "./assets/shaders/bird.frag");

  bird->textures[0] = createTexture("./assets/textures/yellowbird-downflap.png", false, NULL, NULL);
  bird->textures[1] = createTexture("./assets/textures/yellowbird-midflap.png", false, NULL, NULL);
  bird->textures[2] = createTexture("./assets/textures/yellowbird-upflap.png", false, NULL, NULL);

  useShader(bird->shader);
  setInt(bird->shader, "texture0", 0);
  setInt(bird->shader, "texture1", 1);
  setInt(bird->shader, "texture2", 2);

  setMatrix4f(bird->shader, "projection", proj);

  setInt(bird->shader, "t", 1);

  translation(&bird->model, 0, bird->y);
  setMatrix4f(bird->shader, "model", &bird->model);
}

void bird_destroy(Bird *bird) {
  glDeleteVertexArrays(1, &bird->VAO);
  glDeleteBuffers(1, &bird->VBO);
  glDeleteBuffers(1, &bird->EBO);

  destroyShader(bird->shader);
  destroyTexture(bird->textures[0]);
  destroyTexture(bird->textures[1]);
  destroyTexture(bird->textures[2]);
}

void bird_update(Bird *bird, double dt) {
  static Mat4 rot, trans;

  // Flap animation
  bird->t += (float)dt * bird->flapSpeed;
  if (bird->t >= 4) bird->t = 0;

  bird->y -= bird->acc;
  bird->acc += GRAVITY * dt;
  bird->theta = 5 * bird->acc;

  // Update bird model matrix
  translation(&trans, 0, bird->y);
  rotate(&rot, bird->theta);
  matmul(&rot, &trans, &bird->model);

  // Update uniforms
  useShader(bird->shader);
  setInt(bird->shader, "t", (int)floor(bird->t) % 4);
  setMatrix4f(bird->shader, "model", &bird->model);
}

void bird_draw(const Bird *bird) {
  useShader(bird->shader);

  glActiveTexture(GL_TEXTURE0);
  bindTexture(bird->textures[0]);
  glActiveTexture(GL_TEXTURE1);
  bindTexture(bird->textures[1]);
  glActiveTexture(GL_TEXTURE2);
  bindTexture(bird->textures[2]);

  glBindVertexArray(bird->VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bird->EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
