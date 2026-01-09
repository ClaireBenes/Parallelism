#include "Cooker.h"

#include <thread>
#include <chrono>

Cooker::Cooker(MessageQueue<IngredientRequest>& requests,
    MessageQueue<int>& preparedIngredients)
    : requestQueue(requests), readyQueue(preparedIngredients)
{
}

void Cooker::Run()
{
    while (true)
    {
        IngredientRequest req = requestQueue.pop();

        printf("Cooker: preparing ingredient %d\n", req.ingredientId);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        readyQueue.push(req.ingredientId);
    }
}
