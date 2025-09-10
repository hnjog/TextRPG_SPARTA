#include <iostream>
#include <conio.h>

#include "GameManager.h"
#include "ShopManager.h"
#include "BattleManager.h"
#include "Enemy/EnemySpawnManager.h"
#include "DataManager.h"
#include "ItemManager.h"
#include "Character/Player.h"


using namespace std;

GameManager& GameManager::Instance()
{
	static GameManager instance;
	return instance;
}

void GameManager::InitGame()
{
	// 플레이어 초기화
	InitPlayer();

	// 상점 초기화
	ItemManager::GetInstance().Init();
	ShopManager::Instance().InitShop();

	EnemySpawnManager::GetInstance().LoadFromDataManager(DataManager::GetInstance());
}

void GameManager::InitPlayer()
{
	// 캐릭터 생성
	string name;
	Stat stat = Stat();
	stat.attack = 30;
	stat.maxHp = 200;
	stat.currentHp = stat.maxHp;

#if DEV
	player = new Player("player", stat);
#elif Build
	cout << "플레이어 이름을 입력하세요: ";
	getline(cin, name);

	while (GetIsNameValid(name) == false) {
		cout << "[ERROR] 플레이어 이름에 공백을 포함할 수 없습니다.\n";
		cout << "플레이어 이름을 입력하세요: ";
		getline(cin, name);
	}

	player = new Player(name, stat);
#endif
}

bool GameManager::GetIsNameValid(const string& input)
{
	if (input.empty()) return false;

	for (char c : input) {
		if (isspace(static_cast<unsigned char>(c))) {
			return false;
		}
	}
	return true;
}


void GameManager::StartGame()
{
	InitGame();

	// 플레이 선택
	int opt = 0;
	while (opt != -1) {
		system("cls");

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
			cout << "플레이어 스탯확인창을 닫기 위해 아무 키나 누르세요.\n";
			_getch();
			break;
		case 3:
			ShopManager::Instance().VisitShop(this->player);
			break;
		default:
			break;
		}
	}

	delete player;
}