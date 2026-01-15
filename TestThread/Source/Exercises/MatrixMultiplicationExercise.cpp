#include "MatrixMultiplicationExercise.h"

#include <iostream>
#include <thread>

void MatrixMultiplicationExercise::Multiply(const float a[4], const float b[4], float r[4])
{
    std::thread t1(ComputeCell, std::ref(r[0]), a[0], b[0], a[1], b[2]);
    std::thread t2(ComputeCell, std::ref(r[1]), a[0], b[1], a[1], b[3]);
    std::thread t3(ComputeCell, std::ref(r[2]), a[2], b[0], a[3], b[2]);
    std::thread t4(ComputeCell, std::ref(r[3]), a[2], b[1], a[3], b[3]);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

void MatrixMultiplicationExercise::ComputeCell(float& result, float a1, float b1, float a2, float b2)
{
    result = a1 * b1 + a2 * b2;
}

void MatrixMultiplicationExercise::Print(const float m[4])
{
    printf( "(X = %.0f), (Y = %.0f), (Z = %.0f), (W = %.0f)\n", m[0], m[1], m[2], m[3] );
}
