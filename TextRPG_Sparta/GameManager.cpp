#include <iostream>

#include "GameManager.h"
#include "ShopManager.h"
#include "BattleManager.h"
#include "EnemySpawnManager.h"
#include "DataManager.h"
#include "Character/Player.h"

using namespace std;

GameManager& GameManager::Instance()
{
	static GameManager instance;
	return instance;
}

void GameManager::InitGame()
{
	// 상점 초기화
	ShopManager::Instance().InitShop();
	EnemySpawnManager::GetInstance().LoadFromDataManager(DataManager::GetInstance());

}

void GameManager::StartGame()
{
	// 캐릭터 생성
	string name;
	Stat stat = Stat();
	stat.attack = 3;
	stat.maxHp = 100;
	stat.currentHp = stat.maxHp;

#if DEV
	player = new Player("player", stat);
#elif Build
	cout << "플레이어 이름을 입력하세요: ";
	getline(cin, name);

	while (GetIsNameValid(name) || name.empty()) {
		cout << "[ERROR] 플레이어 이름에 공백을 포함할 수 없습니다.\n";
		cout << "플레이어 이름을 입력하세요: ";
		getline(cin, name);
	}

	player = new Player(name, stat);
#endif
	

	// 플레이 선택
	int opt = 0;
	while (opt != -1) {
		cout << "1. 전투\n2. 플레이어 확인\n3. 상점이용\n";
		cout << "선택하세요(게임종료 -1): ";
		cin >> opt;

		switch (opt)
		{	
		case 1:
			if(!BattleManager::GetInstance().StartBattle(player))
				return;
			break;
		case 2:
			player->DisplayStat();
			break;
		case 3:
			ShopManager::Instance().VisitShop(this->player);
			break;
		default:
			break;
		}
	}
}

bool GameManager::GetIsNameValid(const string& input)
{
	for (char c : input) {
		if (isspace(static_cast<unsigned char>(c))) {
			return true;
		}
	}
	return false;
}
