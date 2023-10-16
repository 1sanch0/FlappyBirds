#ifndef MATH_H_
#define MATH_H_

#include <math.h>

typedef struct {
  float data[4 * 4];
} Mat4;

void zeros(Mat4 *mat);
void identity(Mat4 *mat);

void matmul(const Mat4 *a, const Mat4 *b, Mat4 *c);

void orthographic(Mat4 *mat, float left, float right, float bottom, float top, float near, float far);

void translation(Mat4 *mat, float dx, float dy);
//void translationInv(Mat4 *mat, Float dx, Float dy, Float dz);
//void scale(Mat4 *mat, Float dx, Float dy, Float dz);
//void scaleInv(Mat4 *mat, Float dx, Float dy, Float dz);
void rotate(Mat4 *mat, float theta);
//void rotateInv(Mat4 *mat, Float theta);

#endif // MATH_H_
