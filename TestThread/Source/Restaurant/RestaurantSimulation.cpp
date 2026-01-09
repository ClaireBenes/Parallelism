#include "RestaurantSimulation.h"

#include "MessageQueue.h"
#include "Messages.h"
#include "Customer.h"
#include "Waiter.h"
#include "Cooker.h"
#include "Chief.h"

#include <vector>
#include <thread>
#include <random>

RestaurantSimulation::RestaurantSimulation(int maxTables, int numCustomers,
    int numWaiters, int numCookers, int numChiefs)
    : tables(maxTables), numCustomers(numCustomers),
    numWaiters(numWaiters), numCookers(numCookers), numChiefs(numChiefs)
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
    std::vector<Waiter*> waiters;
    std::vector<Cooker*> cookers;
    std::vector<Chief*> chiefs;
    std::vector<std::thread> threads;

    // Create waiters
    for (int i = 0; i < numWaiters; ++i)
    {
        Waiter* w = new Waiter(i + 1, orders, ingredientRequests, meals);
        waiters.push_back(w);
        threads.emplace_back(&Waiter::Run, w);
    }

    // Create cookers
    for (int i = 0; i < numCookers; ++i)
    {
        Cooker* c = new Cooker(i + 1, ingredientRequests, preparedIngredients);
        cookers.push_back(c);
        threads.emplace_back(&Cooker::Run, c);
    }

    // Create chiefs
    for (int i = 0; i < numChiefs; ++i)
    {
        Chief* ch = new Chief(i + 1, preparedIngredients, meals);
        chiefs.push_back(ch);
        threads.emplace_back(&Chief::Run, ch);
    }

    // Customers
    std::vector<std::thread> customerThreads;
    for (int i = 0; i < numCustomers; ++i)
    {
        Customer* c = new Customer(i + 1, orders);
        customerThreads.emplace_back(&Customer::Run, c, std::ref(tables));

        // slower random arrival
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 1000));
    }

    // wait for customers
    for (auto& t : customerThreads)
    {
        t.join();
    }

    // stop all infinite actors
    for (auto w : waiters) w->Stop();
    for (auto c : cookers) c->Stop();
    for (auto ch : chiefs) ch->Stop();

    // join all threads
    for (auto& t : threads)
    {
        t.join();
    }
}
