#include "Waiter.h"

Waiter::Waiter(MessageQueue<Order>& orders,
    MessageQueue<IngredientRequest>& ingredientRequests,
    MessageQueue<MealReady>& meals)
    : orderQueue(orders),
    ingredientQueue(ingredientRequests),
    mealQueue(meals)
{
}

void Waiter::Run()
{
    while (true)
    {
        Order order = orderQueue.pop();

        printf("Waiter: received order from customer %d\n", order.customerId);

        for (int i = 0; i < 3; ++i)
        {
            ingredientQueue.push({ order.ingredients[i] });
        }

        MealReady m = mealQueue.pop();
        printf("Waiter: delivering meal to customer %d\n", m.customerId);

        // signal the customer
        if (order.mealPromise)
        {
            order.mealPromise->set_value();
        }
    }
}
