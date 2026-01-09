#include "SumAlgorithms.h"
#include <thread>
#include <mutex>

static float globalSum;
static std::mutex sumMutex;

float SumAlgorithms::Sequential(const std::vector<float>& elements)
{
    float sum = 0;
    for (float v : elements)
    {
        sum += v;
    }

    return sum;
}

float SumAlgorithms::ThreadLocal(const std::vector<float>& elements, int m)
{
    std::vector<std::thread> threads;
    std::vector<float> localSums(m, 0.0f);

    int chunk = elements.size() / m;

    for (int i = 0; i < m; ++i)
    {
        int start = i * chunk;
        int end = (i == m - 1) ? elements.size() : start + chunk;

        threads.emplace_back([&, i, start, end]()
            {
                float local = 0;
                for (int j = start; j < end; ++j)
                    local += elements[j];
                localSums[i] = local;
            });
    }

    for (auto& t : threads)
        t.join();

    float total = 0;
    for (float s : localSums)
        total += s;

    return total;
}

float SumAlgorithms::WithMutex(const std::vector<float>& elements, int m)
{
    globalSum = 0;
    std::vector<std::thread> threads;

    int chunk = elements.size() / m;

    for (int i = 0; i < m; ++i)
    {
        int start = i * chunk;
        int end = (i == m - 1) ? elements.size() : start + chunk;

        threads.emplace_back([&, start, end]()
            {
                float local = 0;
                for (int i = start; i < end; ++i)
                    local += elements[i];

                std::lock_guard<std::mutex> lock(sumMutex);
                globalSum += local;
            });
    }

    for (auto& t : threads)
        t.join();

    return globalSum;
}

