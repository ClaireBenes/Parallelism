#pragma once

#include "MessageQueue.h"
#include "Messages.h"

#include <atomic>

class Cooker
{
public:
    Cooker(int id, MessageQueue<IngredientRequest>& requests,
        MessageQueue<int>& preparedIngredients);

    void Run();
    void Stop();

private:
    int id;

    MessageQueue<IngredientRequest>& requestQueue;
    MessageQueue<int>& readyQueue;

    std::atomic<bool> stopFlag;
};

