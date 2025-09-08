#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "EnemyData.h"
#include "Character/CharacterBase.h"

struct DropResult {
    int gold = 0;
    int exp = 0;
    std::vector<int> itemIdxList;
};

class Enemy : public CharacterBase
{
protected:
    EnemyData enemyData;
    int level = 1;

public:
    // 생성자 & 초기화
    Enemy(EnemyData& d, int& l)
        : enemyData(d), level(l)
    {
        InitializeFromData();
    }

    void InitializeFromData();


    // 전투
    void Attack(CharacterBase& target);
    virtual void TakeDamage(int damage) override;
    virtual void DisplayStat() override;
    virtual bool IsDead() override { return GetCurrentHp() <= 0; }

    // 보상
    int GetDropGold() const { return enemyData.dropGold; }
    int GetDropExp()  const { return enemyData.dropExp; }
    const std::vector<int>& GetDropItemIdx() const { return enemyData.dropItemIdxVector; }
    const std::vector<int>& GetDropItemChance() const { return enemyData.dropItemChanceVector; }
    DropResult RollDrop() const;   // 확률 적용해서 실제 드랍 산출

    // 스탯 관련
    int GetHpAtLevel(int lv) const { return enemyData.baseHp + enemyData.hpPerLevel * (lv - 1); }
    int GetAttackAtLevel(int lv) const { return enemyData.baseAttack + enemyData.attackPerLevel * (lv - 1); }
    void SetCurrentHpClamped(int hp) {
        const int clamped = std::max(0, std::min(hp, GetMaxHp()));
        SetCurrentHp(clamped);
    }

private:
    // 확률
    static int  RandRange(int l, int r);
    static bool Chance(int percent);
};
