#ifndef SPRITE_H_
#define SPRITE_H_

#include <stdbool.h>

#include <glad/glad.h>

#include "math.h"
#include "shader.h"
#include "texture.h"

typedef struct {
  Mat4 model;

  GLuint VAO, VBO, EBO;
  Shader shader;
  Texture texture;

  int width, height;
} Sprite;

void sprite_init(Sprite *sprite, Mat4 *proj, const char *vertexShader, const char *fragmentShader, const char *texture, float z, bool flip);

void sprite_destroy(Sprite *sprite);

void sprite_draw(const Sprite *sprite);

#endif // SPRITE_H_
