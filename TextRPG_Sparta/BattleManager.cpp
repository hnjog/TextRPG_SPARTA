#include "BattleManager.h"

void BattleManager::StartBattle(Player* player)
{
    m_player = player;
}

bool BattleManager::Update()
{
    return false;
}

void BattleManager::EndBattle()
{
    m_player = nullptr;
}
 