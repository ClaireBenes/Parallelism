#pragma once

#include "TableManager.h"

class RestaurantSimulation
{
public:
    RestaurantSimulation(int maxTables, int numCustomers, int numWaiters, int numCookers, int numChiefs);

    void Start();

private:
    int numCustomers;
    int numWaiters;
    int numCookers;
    int numChiefs;

    TableManager tables;
};
