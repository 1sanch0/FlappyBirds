#ifndef BIRD_H_
#define BIRD_H_

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"
#include "math.h"

typedef struct {
  float x, y;
  float theta;
  float t;
  float flapSpeed;

  GLuint VAO, VBO, EBO;
  Shader shader;
  Texture textures[3];
} Bird;

void bird_init(Bird *bird, Mat4 *proj, int x, int y);

void bird_destroy(Bird *bird);

void bird_update(Bird *bird, bool pressedKeys[], double dt);

void bird_draw(const Bird *bird);

#endif // BIRD_H_
