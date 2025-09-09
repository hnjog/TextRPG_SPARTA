#include "Character/Player.h"
#include "Enemy.h"
#include "ItemManager.h"
#include "EnemySpawnManager.h"
#include "BattleManager.h"
#include <iostream>
#include <random>

BattleManager& BattleManager::GetInstance() {
    static BattleManager instance;
    return instance;
}

void BattleManager::StartBattle(Player* player)
{
    InitBattle(player);

    while (1) {
        if (Battle()) {
            std::cout << "계속 탐사하시겠습니까?(Yes:1, No:2)" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
                continue;
        }
        break;
    }
    EndBattle();
}

void BattleManager::InitBattle(Player* player)
{
    m_player = player;
    m_enemy = std::move(EnemySpawnManager::GetInstance().SpawnEnemy(1, player->GetLevel()));

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);
    turn = dist(rng); // 0 또는 1
    std::cout << "=========================================" << endl;
    if (turn == 0) {
        std::cout << "-------플레이어가 선턴입니다-------" << endl;
    }
    else {
        std::cout << "-------" << m_enemy->GetName() << "이(가) 선턴입니다-------" << endl;
    }

    std::cout << "-&전투가 시작됩니다&-" << endl;
}

bool BattleManager::Battle()
{
    while (1) {
        if (turn == 0) {
            cout << "*플레이어 차례입니다.*" << endl;
            int choice;
            cout << "1. 아이템 사용\n";
            cout << "2. 공격\n";
            cout << "3. 도망\n";
            cin >> choice;

            switch (choice) {
            case 1: {
                int itemIdx;
                cout << "사용할 아이템 번호 입력: ";
                cin >> itemIdx;
                m_player->UseItem(itemIdx, m_enemy.get());
                break;
            }
            case 2:
                cout << "플레이어가 무기를 휘두릅니다";
                m_player->Attack(m_enemy.get());
                break;
            case 3:
                cout << "도망쳤습니다....." << endl;
                return false;
                break;
            default:
                cout << "잘못된 선택입니다.\n";
                break;
            }
            turn = 1;
        }
        else {
            std::cout << "*" << m_enemy->GetName() << "의 차례입니다*" << endl;
            m_enemy.get()->Attack(*m_player);
            turn = 0;
        }

        if (m_player->IsDead()) {
            cout << "패배하였습니다...." << endl;
            m_player->DisplayStat();
            m_player->SetCurrentHp(1);
            return false;
        }
        else if (m_enemy->IsDead()) {
            cout << "승리하였습니다!" << endl;
            DropResult dr = m_enemy->RollDrop();
            m_player->addGold(dr.gold);
            m_player->AddExp(dr.exp);
            for (int i : dr.itemIdxList) {
                m_player->GetItem(ItemManager::GetInstance().MakeItem(i, 1));
            }
            m_player->DisplayStat();
            return true;
        }
    }
}

void BattleManager::EndBattle()
{
    std::cout << "=========================================" << endl;
    m_player = nullptr;
    m_enemy.reset();
}
 