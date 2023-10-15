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

  for (int i = 0; i < 4; i++)
    for (int k = 0; k < 4; k++)
      for (int j = 0; j < 4; j++)
        c->data[i * 4 + j] += a->data[i * 4 + k] * b->data[k * 4 + j];
}

void orthographic(Mat4 *mat, Float left, Float right, Float bottom, Float top, Float near, Float far) {
  identity(mat);

  mat->data[0 * 4 + 0] =  2.0 / (right - left);
  mat->data[1 * 4 + 1] =  2.0 / (top - bottom);
  mat->data[2 * 4 + 2] = -2.0 / (far - near);
  mat->data[3 * 4 + 0] = -(left + right) / (right - left);
  mat->data[3 * 4 + 1] = -(bottom + top) / (top - bottom);
  mat->data[3 * 4 + 2] = -(far + near) / (far - near);
}

//void translation(Mat4 *mat, Float dx, Float dy, Float dz);
//void translationInv(Mat4 *mat, Float dx, Float dy, Float dz);
//void scale(Mat4 *mat, Float dx, Float dy, Float dz);
//void scaleInv(Mat4 *mat, Float dx, Float dy, Float dz);
void rotate(Mat4 *mat, Float theta) {
  identity(mat);

  mat->data[0 * 4 + 0] = cos(theta);
  mat->data[0 * 4 + 1] = -sin(theta);
  mat->data[1 * 4 + 0] = sin(theta);
  mat->data[1 * 4 + 1] = cos(theta);
}

void rotateInv(Mat4 *mat, Float theta) {
  identity(mat);

  mat->data[0 * 4 + 0] = cos(theta);
  mat->data[0 * 4 + 1] = sin(theta);
  mat->data[1 * 4 + 0] = -sin(theta);
  mat->data[1 * 4 + 1] = cos(theta);
}
