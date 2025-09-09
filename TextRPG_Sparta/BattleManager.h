#pragma once
#include <vector>
class Player;
class Enemy;

using namespace std;
class BattleManager
{
private:
	Player* m_player = nullptr;
	vector<Enemy*> m_enemys;

	int turn = 0;
public:
	BattleManager() = default;
	void StartBattle(Player* player);
	void Battle();
	void EndBattle();
};

