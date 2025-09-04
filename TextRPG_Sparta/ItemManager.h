#pragma once

#include <vector>
#include <string>

#include"ItemData.h"

class ItemManager
{
public:
    void Init();

    void PrintAllItems();

private:
    std::vector<ItemData> itemDataVector;
};

