#include "pipes.h"
#include "settings.h"

const float pipe_ar = 320.0f / 52.0f;

typedef struct {
  GLfloat position[2];
  GLfloat uv[2];
} __attribute__((packed)) Vertex;

void pipe_init(Pipe *pipe, Mat4 *proj, float x, float y, bool flip);
void pipe_destroy(Pipe *pipe);
void pipe_update(Pipe *pipe, double dt);
void pipe_draw(const Pipe *pipe);

void pipes_init(Pipes *pipes, Mat4 *proj, float x, float y) {
  pipe_init(&pipes->bottom, proj, x, y - PIPES_VGAP / 2.f, false);
  pipe_init(&pipes->top, proj, x, y + pipe_ar + PIPES_VGAP / 2.f, true);
}

void pipes_destroy(Pipes *pipes) {
  pipe_destroy(&pipes->top);
  pipe_destroy(&pipes->bottom);
}

void pipes_update(Pipes *pipes, double dt) {

  pipes->top.x -= PIPE_SPEED * dt;
  pipes->bottom.x -= PIPE_SPEED * dt;

  if (pipes->top.x < LEFT - 0.5f) {
    pipes->top.x += (1.0f + PIPES_HGAP) * 3.0f;
    pipes->bottom.x += (1.0f + PIPES_HGAP) * 3.0f;
  }

  pipe_update(&pipes->top, dt);
  pipe_update(&pipes->bottom, dt);
}

void pipes_draw(const Pipes *pipes) {
  pipe_draw(&pipes->top);
  pipe_draw(&pipes->bottom);
}

void pipes_setX(Pipes *pipes, float x) {
  pipes->top.x = x;
  pipes->bottom.x = x;
}

void pipes_setY(Pipes *pipes, float y) {
  pipes->top.y = y + pipe_ar + PIPES_VGAP / 2.f;
  pipes->bottom.y = y - PIPES_VGAP / 2.f;
}

void pipe_init(Pipe *pipe, Mat4 *proj, float x, float y, bool flip) {
  pipe->x = x;
  pipe->y = y;

  sprite_init(&pipe->sprite, proj, "./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag", "./assets/textures/pipe-green.png", -0.1, flip);

  useShader(pipe->sprite.shader);
  translation(&pipe->sprite.model, pipe->x, pipe->y);
  setMatrix4f(pipe->sprite.shader, "model", &pipe->sprite.model);
}

void pipe_destroy(Pipe *pipe) {
  sprite_destroy(&pipe->sprite);
}

void pipe_update(Pipe *pipe, double dt) {
  (void)dt;
  // Update pipe model matrix
  translation(&pipe->sprite.model, pipe->x, pipe->y);

  // Update uniforms
  useShader(pipe->sprite.shader);
  setMatrix4f(pipe->sprite.shader, "model", &pipe->sprite.model);
}

void pipe_draw(const Pipe *pipe) {
  sprite_draw(&pipe->sprite);
}
