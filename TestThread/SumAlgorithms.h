#pragma once

#include <vector>

class SumAlgorithms
{
public:
    static float Sequential(const std::vector<float>& elements);
    static float ThreadLocal(const std::vector<float>& elements, int threads);
    static float WithMutex(const std::vector<float>& elements, int threads);
};


