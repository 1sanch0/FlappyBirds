#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdbool.h>
#include "math.h"

typedef GLuint Shader;

Shader createShader(const char *vertex, const char *fragment);
void useShader(Shader shader);
void destroyShader(Shader shader);

void setBool(Shader shader, const char *name, bool value);
void setInt(Shader shader, const char *name, int value);
void setFloat(Shader shader, const char *name, float value);
void setVector3f(Shader shader, const char *name, float x, float y, float z);
void setMatrix4f(Shader shader, const char *name, const Mat4 *mat);

GLuint linkShader(GLuint vertexId, GLuint fragmentId);
GLuint compileShader(const char *filename, GLenum shaderType);

#endif // SHADER_H_
