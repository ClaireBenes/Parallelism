#include "RestaurantSimulation.h"

#include "MessageQueue.h"
#include "Messages.h"
#include "Customer.h"
#include "Waiter.h"
#include "Cooker.h"
#include "Chief.h"

#include <vector>
#include <thread>

RestaurantSimulation::RestaurantSimulation(int numCustomers, int maxTables)
    : numCustomers(numCustomers), tables(maxTables)
{
}

void RestaurantSimulation::Start()
{
    srand((unsigned) time(nullptr));

    // Queues
    MessageQueue<Order> orders;
    MessageQueue<IngredientRequest> ingredientRequests;
    MessageQueue<int> preparedIngredients;
    MessageQueue<MealReady> meals;

    // Actors
    Waiter waiter(orders, ingredientRequests, meals);
    Cooker cooker(ingredientRequests, preparedIngredients);
    Chief chief(preparedIngredients, meals);

    // Threads
    std::thread tWaiter(&Waiter::Run, &waiter);
    std::thread tCooker(&Cooker::Run, &cooker);
    std::thread tChief(&Chief::Run, &chief);

    std::vector<std::thread> customerThreads;
    for (int i = 0; i < numCustomers; ++i)
    {
        Customer* c = new Customer(i + 1, orders);
        customerThreads.emplace_back(&Customer::Run, c, std::ref(tables));

        // simulate random arrival
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 1000));
    }

    for (auto& t : customerThreads)
    {
        t.join();
    }

    // stop infinite actors
    waiter.Stop();
    cooker.Stop();
    chief.Stop();

    tWaiter.join();
    tCooker.join();
    tChief.join();
}
