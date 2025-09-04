#pragma once

#include <vector>
#include <string>

#include"ItemData.h"

class ItemManager
{
public:
    void Init();
    bool Init();

    void PrintAllItems();

private:
    std::unordered_map<int, ItemData> itemMapByIdx;
};

