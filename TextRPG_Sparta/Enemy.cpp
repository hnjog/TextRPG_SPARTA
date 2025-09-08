#include "Enemy.h"
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

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

void Enemy::InitializeFromData()
{
    int hp = GetHpAtLevel(level);
    int atk = GetAttackAtLevel(level);

    SetMaxHp(hp);
    SetCurrentHp(hp);
    SetAttack(atk);
}

void Enemy::Attack(CharacterBase& target)
{
    if (IsDead()) return;

    target.TakeDamage(GetAttack(););

    std::cout << "[����] " << enemyData.name
        << " ����! (" << dmg
        << ") -> �÷��̾� HP : " << target.GetCurrentHp() << "/" << target.GetMaxHp() << "\n";
}

void Enemy::TakeDamage(int damage)
{
    SetCurrentHpClamped(GetCurrentHp() - damage);

    std::cout << "[����] " << enemyData.name
        << " �ǰ�! : -" << damage
        << " | HP " << GetCurrentHp() << "/" << GetMaxHp() << "\n";
}

void Enemy::DisplayStat()
{
    std::cout << "=== ���� ���� ===\n";
    std::cout << "�̸� : " << enemyData.name << " (����." << level << ")\n";
    std::cout << "ü��   : " << GetCurrentHp() << " / " << GetMaxHp() << "\n";
    std::cout << "���ݷ�  : " << GetAttack() << "\n";
    std::cout << "���� : ��� " << GetDropGold() << ", ����ġ " << GetDropExp() << "\n";
}

DropResult Enemy::RollDrop() const
{
    DropResult dr;
    dr.gold = GetDropGold();
    dr.exp = GetDropExp();

    const std::vector<int>& idxs = enemyData.dropItemIdxVector;
    const std::vector<int>& chance = enemyData.dropItemChanceVector;

    const size_t n = std::min(idxs.size(), probs.size());

    for (size_t i = 0; i < n; ++i) {
        if (Chance(probs[i])) dr.itemIdxList.push_back(idxs[i]);
    }
    return dr;
}
