#pragma once

#include "MessageQueue.h"
#include "Messages.h"

#include <atomic>

class Waiter
{
public:
    Waiter(MessageQueue<Order>& orders,
        MessageQueue<IngredientRequest>& ingredientRequests,
        MessageQueue<MealReady>& meals);

    void Run();
    void Stop();

private:
    MessageQueue<Order>& orderQueue;
    MessageQueue<IngredientRequest>& ingredientQueue;
    MessageQueue<MealReady>& mealQueue;

    std::atomic<bool> stopFlag;
};
