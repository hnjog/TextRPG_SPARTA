#include "BattleManager.h"
#include <iostream>
#include <random>

void BattleManager::StartBattle(Player* player)
{
    m_player = player;
    //spawn enemy

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);
    turn = dist(rng); // 0 또는 1

    if (turn == 0) {
        std::cout << "플레이어가 선턴입니다" << endl;
    }
    else {
        std::cout << "이(가) 선턴입니다" << endl;
    }

}

void BattleManager::Battle()
{
    while (1) {
        if (turn == 0) {

            turn = 1;
        }
        else {

            turn = 0;
        }
    }
}

void BattleManager::EndBattle()
{
    m_player = nullptr;
}
 