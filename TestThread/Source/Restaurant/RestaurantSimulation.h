#pragma once

#include "TableManager.h"

class RestaurantSimulation
{
public:
    RestaurantSimulation(int numCustomers, int maxTables);

    void Start();

private:
    int numCustomers;
    TableManager tables;
};
