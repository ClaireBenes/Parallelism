#pragma once

#include "MessageQueue.h"
#include "Messages.h"

class Chief
{
public:
    Chief(MessageQueue<int>& ingredients,
        MessageQueue<MealReady>& meals);

    void Run();

private:
    MessageQueue<int>& ingredientQueue;
    MessageQueue<MealReady>& mealQueue;
};
