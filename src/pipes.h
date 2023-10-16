#ifndef PIPES_H_
#define PIPES_H_

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"

typedef struct {
  float x, y;

  Mat4 model;

  GLuint VAO, VBO, EBO;
  Shader shader;
  Texture texture;
} Pipe;

typedef struct {
  Pipe top, bottom;
} Pipes;

void pipes_init(Pipes *pipes, Mat4 *proj, float x, float y, int gap);

void pipes_destroy(Pipes *pipes);

void pipes_update(Pipes *pipes, bool pressedKeys[], double dt);

void pipes_draw(const Pipes *pipes);

#endif // PIPES_H_
