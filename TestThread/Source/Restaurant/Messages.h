#pragma once

#include <future>

struct Order
{
    int customerId;
    int ingredients[3];
    std::promise<void>* mealPromise = nullptr;
};

struct IngredientRequest
{
    int ingredientId;
};

struct MealReady
{
    int customerId;
};

