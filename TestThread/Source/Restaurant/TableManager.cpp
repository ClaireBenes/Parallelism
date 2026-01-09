#include "TableManager.h"

TableManager::TableManager(int maxTables) : maxTables(maxTables), freeTables(maxTables)
{
}

void TableManager::AcquireTable()
{
    // Customer waits until a table is free
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [&] { return freeTables > 0; });

    --freeTables;
}

// Customer leaves -> frees a table
void TableManager::ReleaseTable()
{
    {
        std::lock_guard<std::mutex> lock(m);
        ++freeTables;
    }
    cv.notify_one();
}
