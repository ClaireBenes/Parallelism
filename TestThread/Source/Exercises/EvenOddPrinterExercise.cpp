#include "EvenOddPrinterExercise.h"

#include <thread>

std::mutex EvenOddPrinterExercise::m;
std::condition_variable EvenOddPrinterExercise::cv;

void EvenOddPrinterExercise::PrintEven(int& number)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&] { return number % 2 == 0 || number > 1000; });

        if (number > 1000) break;

        printf("Even: %d\n", number);
        ++number;
        cv.notify_one();
    }
}

void EvenOddPrinterExercise::PrintOdd(int& number)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&] { return number % 2 != 0 || number > 1000; });

        if (number > 1000) break;

        printf("Odd: %d\n", number);
        ++number;
        cv.notify_one();
    }
}

void EvenOddPrinterExercise::Run()
{
    int number = 0;

    std::thread t1(PrintEven, std::ref(number));
    std::thread t2(PrintOdd, std::ref(number));

    t1.join();
    t2.join();
}

