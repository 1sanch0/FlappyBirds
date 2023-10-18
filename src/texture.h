#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>

typedef GLuint Texture;

Texture createTexture(const char *filename, bool flip, int *width, int *height);
void destroyTexture(Texture texture);
void bindTexture(Texture texture);

#endif // TEXTURE_H_
