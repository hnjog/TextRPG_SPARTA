#include <iostream>

#include "GameManager.h"

using namespace std;

GameManager& GameManager::Instance()
{
	static GameManager instance;
	return instance;
}

void GameManager::StartGame()
{
	// 캐릭터 생성

	// 플레이 선택
	int opt = 0;
	while (opt != -1) {
		cout << "1. 전투\n2. 인벤토리 확인\n3. 상점이용\n";
		cout << "선택하세요(게임종료 -1): ";
		cin >> opt;

	}
}