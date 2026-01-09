#pragma once

#include "MessageQueue.h"
#include "Messages.h"

class Customer
{
public:
    Customer(int id, MessageQueue<Order>& orders);

    void Run();

private:
    int id;
    MessageQueue<Order>& orderQueue;
};
