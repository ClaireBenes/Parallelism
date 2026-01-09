#pragma once

#include "MessageQueue.h"
#include "Messages.h"

#include "TableManager.h"

class Customer
{
public:
    Customer(int id, MessageQueue<Order>& orders);

    void Run(TableManager& tables);

private:
    int id;
    MessageQueue<Order>& orderQueue;
};
