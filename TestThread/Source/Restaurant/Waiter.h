#pragma once

#include "MessageQueue.h"
#include "Messages.h"

class Waiter
{
public:
    Waiter(MessageQueue<Order>& orders,
        MessageQueue<IngredientRequest>& ingredientRequests,
        MessageQueue<MealReady>& meals);

    void Run();

private:
    MessageQueue<Order>& orderQueue;
    MessageQueue<IngredientRequest>& ingredientQueue;
    MessageQueue<MealReady>& mealQueue;
};
