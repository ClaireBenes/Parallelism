#pragma once


class MatrixMultiplicationExercise
{
public:
    static void Multiply(const float a[4], const float b[4], float r[4]);
    static void ComputeCell(float& result, float a1, float b1, float a2, float b2);
    static void Print(const float m[4]);
};

