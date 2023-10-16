#include "math.h"

void zeros(Mat4 *mat) {
  for (int i = 0; i < 4 * 4; i++)
    mat->data[i] = 0.0;
}

void identity(Mat4 *mat) {
  zeros(mat);

  for (int i = 0; i < 4; i++)
    mat->data[i * 4 + i] = 1.0;
}

void matmul(const Mat4 *a, const Mat4 *b, Mat4 *c) {
  zeros(c);

  for (int j = 0; j < 4; j++)
    for (int k = 0; k < 4; k++)
      for (int i = 0; i < 4; i++)
        c->data[j * 4 + i] += a->data[k * 4 + i] * b->data[j * 4 + k];
}

void orthographic(Mat4 *mat, float left, float right, float bottom, float top, float near, float far) {
  identity(mat);

  mat->data[0 * 4 + 0] =  2.0 / (right - left);
  mat->data[1 * 4 + 1] =  2.0 / (top - bottom);
  mat->data[2 * 4 + 2] = -2.0 / (far - near);
  mat->data[0 * 4 + 3] = -(left + right) / (right - left);
  mat->data[1 * 4 + 3] = -(bottom + top) / (top - bottom);
  mat->data[2 * 4 + 3] = -(far + near) / (far - near);
}

void translation(Mat4 *mat, float dx, float dy) {
  identity(mat);

  mat->data[0 * 4 + 3] = dx;
  mat->data[1 * 4 + 3] = dy;
}
//void translationInv(Mat4 *mat, Float dx, Float dy, Float dz);
//void scale(Mat4 *mat, Float dx, Float dy, Float dz);
//void scaleInv(Mat4 *mat, Float dx, Float dy, Float dz);
void rotate(Mat4 *mat, float theta) {
  identity(mat);

  mat->data[0 * 4 + 0] = cos(theta);
  mat->data[0 * 4 + 1] = sin(theta);
  mat->data[1 * 4 + 0] = -sin(theta);
  mat->data[1 * 4 + 1] = cos(theta);
}

//void rotateInv(Mat4 *mat, Float theta);
