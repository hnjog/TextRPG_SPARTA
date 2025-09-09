#pragma once

#include "ItemInstance.h"
#include "EquipDesc.h"

class CharacterBase;

class EquipItem : public ItemInstance
{
public:
	EquipItem();
	EquipItem(int idx, const std::string& name, const std::string& effect, int value, int price, bool isConsumable, bool isStackable, bool isEquipable, ItemEquipParts equipParts, int amount);
	EquipItem(const ItemData& itemData, int amount);

	virtual ~EquipItem();
	
public:
	bool Equip(CharacterBase* target);
	bool Unequip(CharacterBase* target);

	inline bool IsEquipped() const { return equipState == ItemEquipState::IED_Equipped; }
	inline bool IsUnequipped() const { return equipState == ItemEquipState::IES_UnEquipped; }

protected:
	ItemEquipState equipState;
};

