#pragma once
#include "CharacterBase.h"
#include <vector>


class ItemInstance;
class Player :
    public CharacterBase
{
private:
    int     m_experience;
    int     m_gold;
    int     m_level;
    vector<ItemInstance*> m_inventory;
public:
    Player(string name, Stat stat);
    int GetCurrentGold() { return m_gold; }
    int GetCurrentExp() { return m_experience; }

    bool UseItem(int idx, CharacterBase* target);
    void GetItem(ItemInstance* item);

    void AddExp(int exp);

    int getGold() const;
    void addGold(int gold);
    bool useGold(int gold);

    virtual void DisplayStat()override;
    virtual void Attack(CharacterBase* target)override;
    virtual void TakeDamage(int damage)override;
    virtual bool IsDead()override;
};

