#pragma once

#include <mutex>
#include <condition_variable>

class TableManager
{
public:
    TableManager(int maxTables);

    void AcquireTable();
    void ReleaseTable();

private:
    int maxTables;
    int freeTables;
    std::mutex m;
    std::condition_variable cv;
};

