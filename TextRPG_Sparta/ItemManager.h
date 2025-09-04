#pragma once

#include <string>
#include <unordered_map>

#include"ItemData.h"

class ItemInstance;

class ItemManager
{
public:
    static ItemManager& GetInstance();

    bool Init();
    void PrintAllItems() const;

    // 내부에서 아이템을 '생성'한다는 의미에 걸맞도록 수정
    // 생성된 객체를 반환합니다!
    ItemInstance* MakeItem(int idx, int count);
    const ItemData* GetItemData(int idx);

private:
    std::unordered_map<int, ItemData> itemMapByIdx;
};

