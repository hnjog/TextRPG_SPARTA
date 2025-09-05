#pragma once
#include <iostream>
#include "EnemyData.h"
#include "Character/CharacterBase.h"

class Enemy : public CharacterBase
{
protected:
    EnemyData enemyData;
    std::string name;

public:

    Enemy(const std::string& n, EnemyData& d) : name(n), enemyData(d)
    {

    }

    virtual ~Enemy() = default;


    int GetDropGold() const {
        return enemyData.dropGold;
    }

    int GetDropExp() const {
        return enemyData.dropExp;
    }

    const std::vector<int>& GetDropItemIdx() const {
        return enemyData.dropItemIdxVector;
    }

};
