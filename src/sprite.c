#include "sprite.h"

typedef struct {
  GLfloat position[2];
  GLfloat uv[2];
} __attribute__((packed)) Vertex;

  void sprite_init(Sprite *sprite, Mat4 *proj, const char *vertexShader, const char *fragmentShader, const char *texture, bool flip) {
  identity(&sprite->model);

  sprite->texture = createTexture(texture, flip, &sprite->width, &sprite->height);

  float ar = (float)sprite->height / (float)sprite->width; // aspect ratio

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

  glGenVertexArrays(1, &sprite->VAO);
  glBindVertexArray(sprite->VAO);

  glGenBuffers(1, &sprite->VBO);

  glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  // UV attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(1);

  glGenBuffers(1, &sprite->EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);

  sprite->shader = createShader(vertexShader, fragmentShader);

  useShader(sprite->shader);
  setInt(sprite->shader, "texture0", 0);

  setMatrix4f(sprite->shader, "projection", proj);
  setMatrix4f(sprite->shader, "model", &sprite->model);
}

void sprite_destroy(Sprite *sprite) {
  glDeleteVertexArrays(1, &sprite->VAO);
  glDeleteBuffers(1, &sprite->VBO);
  glDeleteBuffers(1, &sprite->EBO);

  destroyShader(sprite->shader);
  destroyTexture(sprite->texture);
}

void sprite_draw(const Sprite *sprite) {
  useShader(sprite->shader);

  glActiveTexture(GL_TEXTURE0);
  bindTexture(sprite->texture);

  glBindVertexArray(sprite->VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
