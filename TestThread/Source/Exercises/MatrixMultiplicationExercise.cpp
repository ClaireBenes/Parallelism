#include "MatrixMultiplicationExercise.h"
#include <iostream>

void MatrixMultiplicationExercise::Multiply(const float a[4], const float b[4], float r[4])
{
    r[0] = a[0] * b[0] + a[1] * b[2];
    r[1] = a[0] * b[1] + a[1] * b[3];
    r[2] = a[2] * b[0] + a[3] * b[2];
    r[3] = a[2] * b[1] + a[3] * b[3];
}

void MatrixMultiplicationExercise::Print(const float m[4])
{
    printf( "(X = %.0f), (Y = %.0f), (Z = %.0f), (W = %.0f)\n", m[0], m[1], m[2], m[3] );
}
