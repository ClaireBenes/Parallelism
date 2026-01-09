#pragma once

#include "MessageQueue.h"
#include "Messages.h"

class Cooker
{
public:
    Cooker(MessageQueue<IngredientRequest>& requests,
        MessageQueue<int>& preparedIngredients);

    void Run();

private:
    MessageQueue<IngredientRequest>& requestQueue;
    MessageQueue<int>& readyQueue;
};

