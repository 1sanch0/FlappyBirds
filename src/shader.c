#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

Shader createShader(const char *vertex, const char *fragment) {
  GLuint vertexShader = compileShader(vertex, GL_VERTEX_SHADER);
  GLuint fragmentShader = compileShader(fragment, GL_FRAGMENT_SHADER);

  Shader program = linkShader(vertexShader, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}

void useShader(Shader shader) {
  glUseProgram(shader);
}

void destroyShader(Shader shader) {
  glDeleteProgram(shader);
}

void setBool(Shader shader, const char *name, bool value) {
  glUniform1i(glGetUniformLocation(shader, name), (int)value);
}

void setInt(Shader shader, const char *name, int value) {
  glUniform1i(glGetUniformLocation(shader, name), value);
}

void setFloat(Shader shader, const char *name, float value) {
  glUniform1f(glGetUniformLocation(shader, name), value);
}

void setVector3f(Shader shader, const char *name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(shader, name), x, y, z);
}

void setMatrix4f(Shader shader, const char *name, const Mat4 *mat) {
  glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, GL_TRUE, mat->data);
}

GLuint linkShader(GLuint vertexId, GLuint fragmentId) {
  GLuint program = glCreateProgram();

  glAttachShader(program, vertexId);
  glAttachShader(program, fragmentId);
  glLinkProgram(program);

  int success;
  char infoLog[1024];
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 1024, NULL, infoLog);
    fprintf(stderr, "ERROR::PROGRAM_LINKING_ERROR\n%s\n -- --------------------------------------------------- -- \n", infoLog);

    exit(1);
  }

  return program;
}

GLuint compileShader(const char *filename, GLenum shaderType) {
  GLuint id = glCreateShader(shaderType);

  // Read file
  int fd;
  if ((fd = open(filename, O_RDONLY)) < 0) {
    fprintf(stderr, "(%s) ", filename);
    perror("Error opening file");
    exit(1);
  }

  off_t nbytes = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  char *source = (char *)calloc(nbytes, sizeof(char));
  char buffer[BUFSIZ] = {0};
  size_t c = 0;

  ssize_t n;
  while ((n = read(fd, buffer, BUFSIZ)) > 0) {
    memcpy(source + c, buffer, (size_t)n);
    c += n;
  }
  
  close(fd);

  if (n < 0) {
    fprintf(stderr, "(%s) ", filename);
    perror("Error reading file");
    exit(1);
  }
  source[nbytes - 1] = '\0';

  // compile
  const GLchar *shaderSource = source;
  glShaderSource(id, 1, &shaderSource, NULL);
  glCompileShader(id);

  int success;
  char infoLog[1024];
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(id, 1024, NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER_COMPILATION_ERROR: \n%s\n -- --------------------------------------------------- -- \n", infoLog);

    printf("\n\n%s\n", source);
    exit(1);
  }

  // free source code memory
  free(source);

  return id;
}
