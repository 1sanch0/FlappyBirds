#include "pipes.h"

typedef struct {
  GLfloat position[2];
  GLfloat uv[2];
} __attribute__((packed)) Vertex;

void pipe_init(Pipe *pipe, Mat4 *proj, float x, float y, bool flip);
void pipe_destroy(Pipe *pipe);
void pipe_update(Pipe *pipe, double dt);
void pipe_draw(const Pipe *pipe);

void pipes_init(Pipes *pipes, Mat4 *proj, float x, float y, int gap) {
  float pipe_ar = 320.0f / 52.0f;
  pipe_init(&pipes->bottom, proj, x, y - gap / 2, false);
  pipe_init(&pipes->top, proj, x, y + pipe_ar + gap / 2, true);
}

void pipes_destroy(Pipes *pipes) {
  pipe_destroy(&pipes->top);
  pipe_destroy(&pipes->bottom);
}

void pipes_update(Pipes *pipes, bool pressedKeys[], double dt) {
  // ONLY WHILE DEVEL DELETE LATER (TODO)
  if (pressedKeys[GLFW_KEY_K]) {
    pipes->top.y += dt;
    pipes->bottom.y += dt;
  }
  if (pressedKeys[GLFW_KEY_J]) {
    pipes->top.y -= dt;
    pipes->bottom.y -= dt;
  }
  if (pressedKeys[GLFW_KEY_L]) {
    pipes->top.x += dt;
    pipes->bottom.x += dt;
  }
  if (pressedKeys[GLFW_KEY_H]) {
    pipes->top.x -= dt;
    pipes->bottom.x -= dt;
  }
  // END ONLY WHILE DEVEL DELETE LATER (TODO)

  pipe_update(&pipes->top, dt);
  pipe_update(&pipes->bottom, dt);
}

void pipes_draw(const Pipes *pipes) {
  pipe_draw(&pipes->top);
  pipe_draw(&pipes->bottom);
}

void pipe_init(Pipe *pipe, Mat4 *proj, float x, float y, bool flip) {
  pipe->x = x;
  pipe->y = y;

  // Pipe dimentions: width x height = 52 x 320
  float ar = 320.0f / 52.0f;

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

  glGenVertexArrays(1, &pipe->VAO);
  glBindVertexArray(pipe->VAO);

  glGenBuffers(1, &pipe->VBO);

  glBindBuffer(GL_ARRAY_BUFFER, pipe->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // Position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  // UV attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
  glEnableVertexAttribArray(1);

  glGenBuffers(1, &pipe->EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipe->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);

  pipe->shader = createShader("./assets/shaders/pipe.vert", "./assets/shaders/pipe.frag");
  pipe->texture = createTexture("./assets/textures/pipe-green.png", flip);


  useShader(pipe->shader);
  setInt(pipe->shader, "texture0", 0);

  setMatrix4f(pipe->shader, "projection", proj);
}

void pipe_destroy(Pipe *pipe) {
  glDeleteVertexArrays(1, &pipe->VAO);
  glDeleteBuffers(1, &pipe->VBO);
  glDeleteBuffers(1, &pipe->EBO);

  destroyShader(pipe->shader);
  destroyTexture(pipe->texture);
}

void pipe_update(Pipe *pipe, double dt) {
  // Update pipe model matrix
  translation(&pipe->model, pipe->x, pipe->y);

  // Update uniforms
  useShader(pipe->shader);
  setMatrix4f(pipe->shader, "model", &pipe->model);
}

void pipe_draw(const Pipe *pipe) {
  useShader(pipe->shader);

  glActiveTexture(GL_TEXTURE0);
  bindTexture(pipe->texture);

  glBindVertexArray(pipe->VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipe->EBO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
