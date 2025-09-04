#pragma once

#include<string>

struct ItemData
{
	int idx;
	std::string name;
	std::string effect;
	int value;
	int price;
	bool isConsumable;
	bool isStackable;
};