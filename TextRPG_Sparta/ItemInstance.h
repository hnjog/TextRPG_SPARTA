#pragma once

#include"ItemData.h"

class ItemInstance
{
public:
	ItemInstance();
	ItemInstance(int idx, std::string& name, std::string& effect, int value, int price, bool isConsumable, bool isStackable, int amount);
	ItemInstance(ItemData& itemData, int amount);

	bool UseItem(class CharacterBase* target);

public:
	inline int GetItemIdx() const { return itemData.idx; }
	inline const std::string& GetItemName() const { return itemData.name; }
	inline const std::string& GetItemEffect() const { return itemData.effect; }
	inline int GetItemValue() const { return itemData.value; }
	inline int GetItemPrice() const { return itemData.price; }
	inline bool isConsumableItem() const { return itemData.isConsumable; }
	inline bool isStackableItem() const { return itemData.isStackable; }
	inline bool GetItemStock() const { return stock; }

protected:
	ItemData itemData;
	int stock;
};

