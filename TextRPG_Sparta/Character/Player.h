#pragma once
#include "CharacterBase.h"
#include <vector>


class ItemInstance;
class Player :
    public CharacterBase
{
private:
    int m_experience;
    int m_gold;
    vector<ItemInstance> m_inventory;
public:
    Player(string name, Stat stat);
    int GetCurrentGold() { return m_gold; }
    int GetCurrentExp() { return m_experience; }

    bool UseItem(int idx, CharacterBase* target);
    void GetItem(int idx);
};

