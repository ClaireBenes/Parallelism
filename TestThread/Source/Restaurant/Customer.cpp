#include "Customer.h"

#include <thread>
#include <chrono>
#include <future>

Customer::Customer(int id, MessageQueue<Order>& orders)
    : id(id), orderQueue(orders)
{
}

void Customer::Run()
{
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

    // wait for meal to be delivered
    mealPromise.get_future().get();

    printf("Customer %d: eating...\n", id);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    printf("Customer %d: leaving restaurant\n", id);
}
