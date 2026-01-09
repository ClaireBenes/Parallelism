#include "Customer.h"

#include <thread>
#include <chrono>
#include <future>
#include <random>

Customer::Customer(int id, MessageQueue<Order>& orders)
    : id(id), orderQueue(orders)
{
}

void Customer::Run(TableManager& tables)
{
    printf("Customer %d: arrives, waiting for a table\n", id);
    tables.AcquireTable();  // wait until a table is free
    printf("Customer %d: seated at table\n", id);

    // Prepare order with promise
    Order order;
    order.customerId = id;

    // generate random ingredients
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    for (int i = 0; i < 3; ++i)
    {
        order.ingredients[i] = dis(gen);
    }

    std::promise<void> mealPromise;
    order.mealPromise = &mealPromise;

    printf("Customer %d: ordering ingredients [%d %d %d]\n",
        id, order.ingredients[0], order.ingredients[1], order.ingredients[2]);

    orderQueue.push(order);

    // Wait for meal delivery
    mealPromise.get_future().get();

    printf("Customer %d: eating...\n", id);
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    printf("Customer %d: leaving\n", id);
    tables.ReleaseTable();
}
