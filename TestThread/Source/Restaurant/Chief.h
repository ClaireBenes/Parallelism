#pragma once

#include "MessageQueue.h"
#include "Messages.h"

#include <atomic>

class Chief
{
public:
    Chief(int id, MessageQueue<int>& ingredients,
        MessageQueue<MealReady>& meals);

    void Run();
    void Stop();

private:
    int id;

    MessageQueue<int>& ingredientQueue;
    MessageQueue<MealReady>& mealQueue;

    std::atomic<bool> stopFlag;
};
