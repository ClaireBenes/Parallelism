#include "Waiter.h"

Waiter::Waiter(MessageQueue<Order>& orders,
    MessageQueue<IngredientRequest>& ingredientRequests,
    MessageQueue<MealReady>& meals)
    : orderQueue(orders),
    ingredientQueue(ingredientRequests),
    mealQueue(meals), stopFlag(false)
{
}

void Waiter::Run()
{
    while (!stopFlag)
    {
        if (!orderQueue.empty())
        {
            Order order = orderQueue.pop();
            printf("Waiter: received order from customer %d\n", order.customerId);

            for (int i = 0; i < 3; ++i)
                ingredientQueue.push({ order.ingredients[i] });

            // wait for meal from Chief
            mealQueue.pop();
            printf("Waiter: delivering meal to customer %d\n", order.customerId);

            if (order.mealPromise)
                order.mealPromise->set_value();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void Waiter::Stop()
{
    stopFlag = true;
}
