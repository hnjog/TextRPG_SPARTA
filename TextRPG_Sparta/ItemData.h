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

	ItemData()
		:idx(0),
		name(""),
		effect(""),
		value(0),
		price(0),
		isConsumable(false),
		isStackable(false)
	{
	}

	ItemData(int idx, std::string& name, std::string& effect, int value, bool isConsume, bool isStackable)
		:idx(idx),
		name(name),
		effect(effect),
		value(value),
		price(price),
		isConsumable(isConsumable),
		isStackable(isStackable)
	{
	}
};