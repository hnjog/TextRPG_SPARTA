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

bool BattleManager::StartBattle(Player* player)
{
    InitBattle(player);
    int result;
    while (1) {
        result = Battle();
        if (result == 1) {
            if (bossStage) {
                std::cout << "보스를 잡았습니다" << endl;
                std::cout << "게임을 클리어하였습니다" << endl;
                result = -1;
            }
            else {
                std::cout << "계속 탐사하시겠습니까?(Yes:1, No:2)" << endl;
                int choice;
                cin >> choice;
                if (choice == 1) {
                    InitBattle(player);
                    continue;
                }
            }
        }
        break;
    }
    EndBattle();

    if (result == -1) {
        return false;
    }

    return true;
}

void BattleManager::InitBattle(Player* player)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);
    turn = dist(rng); // 0 또는 1
    std::uniform_int_distribution<int> dist2(1,3);

    m_player = player;
    m_enemy = std::move(EnemySpawnManager::GetInstance().SpawnEnemy(dist2(rng), player->GetLevel()));
    if (player->GetLevel() == 10) {
        m_enemy->UpgradeBoss();
        bossStage = true;
    }

    
    std::cout << "=========================================" << endl;
    if (turn == 0) {
        std::cout << "-------플레이어가 선턴입니다-------" << endl;
    }
    else {
        std::cout << "-------" << m_enemy.get()->GetName() << "이(가) 선턴입니다-------" << endl;
    }

    std::cout << "-&전투가 시작됩니다&-" << endl;
}

int BattleManager::Battle()
{
    while (1) {
        system("cls"); // 화면 지우기 (윈도우 환경일 경우) / 필요 없으면 제거
        cout << "==============================\n";
        cout << "       ⚔ 현재 전투 상태 ⚔\n";
        cout << "==============================\n\n";

        cout << "[플레이어 상태]\n";
        m_player->DisplayStat();
        cout << "\n";

        cout << "[적 상태]\n";
        m_enemy->DisplayStat();
        cout << "\n==============================\n\n";

        if (turn == 0) {
            cout << "▶ 플레이어 차례입니다.\n\n";
            cout << " 선택지를 고르세요:\n";
            cout << "  1. 아이템 사용\n";
            cout << "  2. 공격\n";
            cout << "  3. 도망\n";
            cout << "--------------------------------\n";
            cout << "입력: ";

            int choice;
            cin >> choice;

            switch (choice) {
            case 1: {
                int itemIdx;
                cout << "\n사용할 아이템 번호 입력: ";
                cin >> itemIdx;
                m_player->UseItem(itemIdx, m_player);
                break;
            }
            case 2:
                cout << "\n플레이어가 무기를 휘두릅니다!\n";
                m_player->Attack(m_enemy.get());
                break;
            case 3:
                cout << "\n⚠ 도망쳤습니다...\n";
                return 2;
            default:
                cout << "\n잘못된 선택입니다. 다시 입력하세요.\n";
                break;
            }
            turn = 1;
        }
        else {
            cout << "▶ " << m_enemy->GetName() << "의 차례입니다!\n\n";
            m_enemy->Attack(*m_player);
            turn = 0;
        }

        cout << "\n==============================\n";

        if (m_player->IsDead()) {
            cout << "💀 패배하였습니다.... 💀\n";
            m_player->DisplayStat();
            m_player->SetCurrentHp(1);
            return -1;
        }
        else if (m_enemy->IsDead()) {
            cout << "🎉 승리하였습니다! 🎉\n\n";
            DropResult dr = m_enemy->RollDrop();
            m_player->addGold(dr.gold);
            m_player->AddExp(dr.exp);

            cout << "획득한 보상:\n";
            cout << "  - 골드: " << dr.gold << "\n";
            cout << "  - 경험치: " << dr.exp << "\n";

            for (int i : dr.itemIdxList) {
                cout << "  - 아이템 획득: " << i << "\n";
                m_player->GetItem(ItemManager::GetInstance().MakeItem(i, 1));
            }
            cout << "\n==============================\n";
            m_player->DisplayStat();
            return 1;
        }

        cout << "\n아무 키나 입력하면 다음 턴으로 진행합니다";
        cin.ignore();
        cin.get();
    }
}

void BattleManager::EndBattle()
{
    std::cout << "=========================================" << endl;
    m_player = nullptr;
    m_enemy.reset();
}
 