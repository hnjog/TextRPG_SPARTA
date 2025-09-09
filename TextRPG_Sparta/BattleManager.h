#pragma once
#include <vector>
class Player;
class Enemy;

using namespace std;
class BattleManager
{
private:
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;

	int turn = 0;
public:
	BattleManager() = default;
	void StartBattle(Player* player);
	void Battle();
	void EndBattle();
};

