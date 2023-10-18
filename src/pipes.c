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

  sprite_init(&pipe->sprite, proj, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/pipe-green.png", -0.1, flip);
}

void pipe_destroy(Pipe *pipe) {
  sprite_destroy(&pipe->sprite);
}

void pipe_update(Pipe *pipe, double dt) {
  // Update pipe model matrix
  translation(&pipe->sprite.model, pipe->x, pipe->y);

  // Update uniforms
  useShader(pipe->sprite.shader);
  setMatrix4f(pipe->sprite.shader, "model", &pipe->sprite.model);
}

void pipe_draw(const Pipe *pipe) {
  sprite_draw(&pipe->sprite);
}
