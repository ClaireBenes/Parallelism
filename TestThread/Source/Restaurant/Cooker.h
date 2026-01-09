#pragma once

#include "MessageQueue.h"
#include "Messages.h"

#include <atomic>

class Cooker
{
public:
    Cooker(MessageQueue<IngredientRequest>& requests,
        MessageQueue<int>& preparedIngredients);

    void Run();
    void Stop();

private:
    MessageQueue<IngredientRequest>& requestQueue;
    MessageQueue<int>& readyQueue;

    std::atomic<bool> stopFlag;
};

