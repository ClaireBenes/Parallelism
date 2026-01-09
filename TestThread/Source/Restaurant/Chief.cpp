#include "Chief.h"

#include <thread>
#include <chrono>

Chief::Chief(int id,MessageQueue<int>& ingredients,
    MessageQueue<MealReady>& meals)
    : id(id), ingredientQueue(ingredients), mealQueue(meals), stopFlag(false)
{
}

void Chief::Run()
{
    while (!stopFlag)
    {
        if (ingredientQueue.empty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        int i1 = ingredientQueue.pop();
        int i2 = ingredientQueue.pop();
        int i3 = ingredientQueue.pop();

        printf("Chief %d: assembling meal [%d %d %d]\n", id, i1, i2, i3);

        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        mealQueue.push({ 1 });
    }
}

void Chief::Stop()
{
    stopFlag = true;
}
