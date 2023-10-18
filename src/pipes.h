#ifndef PIPES_H_
#define PIPES_H_

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"
#include "sprite.h"

typedef struct {
  float x, y;

  Sprite sprite;
} Pipe;

typedef struct {
  Pipe top, bottom;
} Pipes;

void pipes_init(Pipes *pipes, Mat4 *proj, float x, float y, int gap);

void pipes_destroy(Pipes *pipes);

void pipes_update(Pipes *pipes, bool pressedKeys[], double dt);

void pipes_draw(const Pipes *pipes);

#endif // PIPES_H_
