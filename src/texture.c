#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture createTexture(const char *filename, bool flip) {
  Texture tex;

  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  stbi_set_flip_vertically_on_load(!flip);
  int width, height, channels;
  stbi_uc *data = stbi_load(filename, &width, &height, &channels, 0);
  if (data == NULL) {
    fprintf(stderr, "(%s) Failed to load texture!\n", filename);
    exit(1);
  }

  int format = GL_RGBA;
  if (channels == 1)
    format = GL_RED;
  if (channels == 3)
    format = GL_RGB;

  format = GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  return tex;
}

void destroyTexture(Texture texture) {
  glDeleteTextures(1, &texture);
}

void bindTexture(Texture texture) {
  glBindTexture(GL_TEXTURE_2D, texture);
}
