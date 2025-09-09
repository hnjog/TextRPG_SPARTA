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
public:
	BattleManager() = default;
	void StartBattle(Player* player);
	bool Update();
	void EndBattle();
};

