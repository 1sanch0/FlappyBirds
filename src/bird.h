#ifndef BIRD_H_
#define BIRD_H_

#include <glad/glad.h>

#include "shader.h"
#include "texture.h"
#include "math.h"

typedef struct {
  float y, acc;
  float theta;
  float t;
  float flapSpeed;

  Mat4 model;

  GLuint VAO, VBO, EBO;
  Shader shader;
  Texture textures[3];
} Bird;

void bird_init(Bird *bird, Mat4 *proj, float y);

void bird_destroy(Bird *bird);

void bird_update(Bird *bird, bool pressedKeys[], double dt);

void bird_draw(const Bird *bird);

#endif // BIRD_H_
