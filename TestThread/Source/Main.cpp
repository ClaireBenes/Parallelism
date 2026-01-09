#include "Exercises/HelloWordExercise.h"
#include "Exercises/MatrixMultiplicationExercise.h"
#include "Exercises/EvenOddPrinterExercise.h"
#include "Exercises/SumAlgorithmsExercise.h"
#include "Restaurant/RestaurantSimulation.h"

#include <vector>
#include <cstdio>

int main()
{
    // Hello World
    printf("Hello Word Exercise : \n");
    HelloWordExercise::SayHello();
    printf("\n----------------\n\n");

    // Matrix multiplication
    printf("Matrix Multiplication Exercise : \n");
    float mat1[4] = { 1, 1, 2, 2 };
    float mat2[4] = { 2, 2, 1, 1 };
    float mat3[4];

    MatrixMultiplicationExercise::Multiply(mat1, mat2, mat3);
    MatrixMultiplicationExercise::Print(mat3);
    printf("\n----------------\n\n");

    // Even / Odd threads
    //printf("Even Odd Printer Exercise \n");
    //EvenOddPrinterExercise::Run();
    //printf("\n----------------\n\n");

    // Sum algorithms
    printf("Sum Algorithms Exercise : \n");
    std::vector<float> list(1000, 3.0f);
    int threads = 4;

    printf("Sequential sum: %.1f\n",
        SumAlgorithmsExercise::Sequential(list));

    printf("Thread-local sum: %.1f\n",
        SumAlgorithmsExercise::ThreadLocal(list, threads));

    printf("Mutex sum: %.1f\n",
        SumAlgorithmsExercise::WithMutex(list, threads));
    printf("\n----------------\n\n");

    // Restaurant Simulation
    printf("Restaurant Simulation Exercise : \n");
    RestaurantSimulation simulation;
    simulation.Start();
    printf("\n----------------\n\n");

    return 0;
}
