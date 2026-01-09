#include "RestaurantSimulation.h"

#include "MessageQueue.h"
#include "Messages.h"
#include "Customer.h"
#include "Waiter.h"
#include "Cooker.h"
#include "Chief.h"

#include <thread>

void RestaurantSimulation::Start()
{
    srand((unsigned) time(nullptr));

    MessageQueue<Order> orders;
    MessageQueue<IngredientRequest> ingredientRequests;
    MessageQueue<int> preparedIngredients;
    MessageQueue<MealReady> meals;

    Customer customer(1, orders);
    Waiter waiter(orders, ingredientRequests, meals);
    Cooker cooker(ingredientRequests, preparedIngredients);
    Chief chief(preparedIngredients, meals);

    std::thread tCustomer(&Customer::Run, &customer);
    std::thread tWaiter(&Waiter::Run, &waiter);
    std::thread tCooker(&Cooker::Run, &cooker);
    std::thread tChief(&Chief::Run, &chief);

    tCustomer.join();
    tWaiter.join();

    tCooker.detach();
    tChief.detach();
}
