#include "Chief.h"

#include <thread>
#include <chrono>

Chief::Chief(MessageQueue<int>& ingredients,
    MessageQueue<MealReady>& meals)
    : ingredientQueue(ingredients), mealQueue(meals)
{
}

void Chief::Run()
{
    int i1 = ingredientQueue.pop();
    int i2 = ingredientQueue.pop();
    int i3 = ingredientQueue.pop();

    printf("Chief: assembling meal [%d %d %d]\n", i1, i2, i3);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    mealQueue.push({ 1 });
}
