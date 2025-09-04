#pragma once

#include"ItemData.h"

class ItemInstance
{
public:
	ItemInstance();
	ItemInstance(int idx, std::string& name, std::string& effect, int value,int price, bool isConsumable, bool isStackable, int amount);
	ItemInstance(ItemData& itemData, int amount);

	bool UseItem(class CharacterBase* target);

protected:
	ItemData itemData;
	int stock;
};

