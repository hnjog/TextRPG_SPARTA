#pragma once

#include<string>
#include"EquipDesc.h"

struct ItemData
{
	int idx;
	std::string name;
	std::string effect;
	int value;
	int price;
	bool isConsumable;
	bool isStackable;
	bool isEquipable;
	ItemEquipParts equipParts;

	ItemData()
		:idx(0),
		name(""),
		effect(""),
		value(0),
		price(0),
		isConsumable(false),
		isStackable(false),
		isEquipable(false),
		equipParts(ItemEquipParts::IEP_NONE)
	{
	}

	ItemData(int idx, std::string& name, std::string& effect, int value,int price, bool isConsumable, bool isStackable, bool isEquipable, ItemEquipParts equipParts)
		:idx(idx),
		name(name),
		effect(effect),
		value(value),
		price(price),
		isConsumable(isConsumable),
		isStackable(isStackable),
		isEquipable(isEquipable),
		equipParts(equipParts)
	{
	}
};