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
	bool bossStage = false;
public:
	static BattleManager& GetInstance();
	BattleManager() = default;
	bool StartBattle(Player* player);
	void InitBattle(Player* player);
	int Battle();
	void EndBattle();
};

