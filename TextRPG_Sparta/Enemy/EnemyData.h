#pragma once

#include<string>
#include<vector>

struct EnemyData
{
	int idx;
	std::string name;
	int baseHp;
	int baseAttack;
	int hpPerLevel;
	int attackPerLevel;
	int dropGold;
	int dropExp;
	std::vector<int> dropItemIdxVector;
	std::vector<int> dropItemChanceVector;
};