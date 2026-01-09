#pragma once

#include <mutex>
#include <condition_variable>

class EvenOddPrinterExercise
{
public:
    static void Run();

private:
    static void PrintEven(int& number);
    static void PrintOdd(int& number);

    static std::mutex m;
    static std::condition_variable cv;
};

