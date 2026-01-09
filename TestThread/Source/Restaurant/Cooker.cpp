#include "Cooker.h"

#include <thread>
#include <chrono>

Cooker::Cooker(MessageQueue<IngredientRequest>& requests,
    MessageQueue<int>& preparedIngredients)
    : requestQueue(requests), readyQueue(preparedIngredients), stopFlag(false)
{
}

void Cooker::Run()
{
    while (!stopFlag)
    {
        if (!requestQueue.empty())
        {
            IngredientRequest req = requestQueue.pop();
            printf("Cooker: preparing ingredient %d\n", req.ingredientId);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            readyQueue.push(req.ingredientId);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void Cooker::Stop()
{
    stopFlag = true;
}
