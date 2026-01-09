#include "Customer.h"

#include <thread>
#include <chrono>
#include <future>

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
    for (int i = 0; i < 3; ++i)
    {
        order.ingredients[i] = rand() % 10;
    }

    std::promise<void> mealPromise;
    order.mealPromise = &mealPromise;

    printf("Customer %d: ordering ingredients [%d %d %d]\n",
        id, order.ingredients[0], order.ingredients[1], order.ingredients[2]);
    orderQueue.push(order);

    // Wait for meal delivery
    mealPromise.get_future().get();

    printf("Customer %d: eating...\n", id);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    printf("Customer %d: leaving\n", id);
    tables.ReleaseTable();
}
