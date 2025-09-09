#pragma once
#include <vector>
class Player;
class Enemy;

using namespace std;
class BattleManager
{
private:
	Player* m_player = nullptr;
	std::unique_ptr<Enemy> m_enemy;

	int turn = 0;
public:
	static BattleManager& GetInstance();
	BattleManager() = default;
	void StartBattle(Player* player);
	void InitBattle(Player* player);
	bool Battle();
	void EndBattle();
};

