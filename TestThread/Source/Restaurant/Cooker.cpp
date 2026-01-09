#include "Cooker.h"

#include <thread>
#include <chrono>

Cooker::Cooker(int id, MessageQueue<IngredientRequest>& requests,
    MessageQueue<int>& preparedIngredients)
    : id(id), requestQueue(requests), readyQueue(preparedIngredients), stopFlag(false)
{
}

void Cooker::Run()
{
    while (!stopFlag)
    {
        if (!requestQueue.empty())
        {
            IngredientRequest req = requestQueue.pop();
            printf("Cooker %d: preparing ingredient %d\n", id, req.ingredientId);

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
