#ifndef MATH_H_
#define MATH_H_

#include <math.h>

typedef float Float;

typedef struct {
  Float data[4 * 4];
} Mat4;

void zeros(Mat4 *mat);
void identity(Mat4 *mat);

void matmul(const Mat4 *a, const Mat4 *b, Mat4 *c);

void orthographic(Mat4 *mat, Float left, Float right, Float bottom, Float top, Float near, Float far);

//void translation(Mat4 *mat, Float dx, Float dy, Float dz);
//void translationInv(Mat4 *mat, Float dx, Float dy, Float dz);
//void scale(Mat4 *mat, Float dx, Float dy, Float dz);
//void scaleInv(Mat4 *mat, Float dx, Float dy, Float dz);
void rotate(Mat4 *mat, Float theta);
void rotateInv(Mat4 *mat, Float theta);

#endif // MATH_H_
