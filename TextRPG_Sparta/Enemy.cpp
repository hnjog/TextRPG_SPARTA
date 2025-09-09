#include "Enemy.h"
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

// 확률 함수
int Enemy::RandRange(int l, int r) {
    static thread_local std::mt19937 rng{
        (uint32_t)std::chrono::steady_clock::now().time_since_epoch().count()
    };
    return std::uniform_int_distribution<int>(l, r)(rng);
}

bool Enemy::Chance(int percent) {
    percent = std::max(0, std::min(percent, 100));
    return RandRange(1, 100) <= percent;
}

//초기화
void Enemy::InitializeFromData()
{
    int hp = GetHpAtLevel(level);
    int atk = GetAttackAtLevel(level);

    SetMaxHp(hp);
    SetCurrentHp(hp);
    SetAttack(atk);
}

//  ===== 전투 =====
void Enemy::Attack(CharacterBase& target)
{
    if (IsDead()) return;

    target.TakeDamage(GetAttack());

    std::cout << "[몬스터] " << enemyData.name
        << " 공격! (" << GetAttack()
        << ") -> 플레이어 HP : " << target.GetCurrentHp() << "/" << target.GetMaxHp() << "\n";
}

void Enemy::TakeDamage(int damage)
{
    SetCurrentHpClamped(GetCurrentHp() - damage);

    std::cout << "[몬스터] " << enemyData.name
        << " 피격! : -" << damage
        << " | HP " << GetCurrentHp() << "/" << GetMaxHp() << "\n";
}

// 상태 표시
void Enemy::DisplayStat()
{
    std::cout << "=== 몬스터 스탯 ===\n";
    std::cout << "이름 : " << enemyData.name << " (레벨." << level << ")\n";
    std::cout << "체력   : " << GetCurrentHp() << " / " << GetMaxHp() << "\n";
    std::cout << "공격력  : " << GetAttack() << "\n";
    std::cout << "보상 : 골드 " << GetDropGold() << ", 경험치 " << GetDropExp() << "\n";
}

// 확률에 따라 보상 출력
DropResult Enemy::RollDrop() const
{
    DropResult dr;
    dr.gold = GetDropGold();
    dr.exp = GetDropExp();

    const std::vector<int>& idxs = enemyData.dropItemIdxVector;
    const std::vector<int>& chance = enemyData.dropItemChanceVector;

    const size_t n = std::min(idxs.size(), chance.size());

    for (size_t i = 0; i < n; ++i) {
        if (Chance(chance[i])) dr.itemIdxList.push_back(idxs[i]);
    }
    return dr;
}
