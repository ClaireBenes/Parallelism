#include "HelloWordExercise.h"
#include "MatrixMultiplicationExercise.h"
#include "EvenOddPrinter.h"
#include "SumAlgorithms.h"

#include <vector>
#include <cstdio>

int main()
{
    // Hello World
    HelloWordExercise::SayHello();

    // Matrix multiplication
    float mat1[4] = { 1, 1, 2, 2 };
    float mat2[4] = { 2, 2, 1, 1 };
    float mat3[4];

    MatrixMultiplicationExercise::Multiply(mat1, mat2, mat3);
    MatrixMultiplicationExercise::Print(mat3);

    // Even / Odd threads
    //EvenOddPrinter::Run();

    // Sum algorithms
    std::vector<float> list(1000, 3.0f);
    int threads = 4;

    printf("Sequential sum: %.1f\n",
        SumAlgorithms::Sequential(list));

    printf("Thread-local sum: %.1f\n",
        SumAlgorithms::ThreadLocal(list, threads));

    printf("Mutex sum: %.1f\n",
        SumAlgorithms::WithMutex(list, threads));

    return 0;
}
