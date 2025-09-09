#include "EquipItem.h"
#include "EffectManager.h"
#include "EffectDescriptor.h"
#include"Character/CharacterBase.h"

EquipItem::EquipItem()
	:ItemInstance()
{
	equipState = ItemEquipState::IES_UnEquipped;
}

EquipItem::EquipItem(int idx, const std::string& name, const std::string& effect, int value, int price, bool isConsumable, bool isStackable, bool isEquipable, ItemEquipParts equipParts, int amount)
	:ItemInstance(idx, name, effect, value, price, isConsumable, isStackable, isEquipable, equipParts, amount)
{
	equipState = ItemEquipState::IES_UnEquipped;
}

EquipItem::EquipItem(const ItemData& itemData, int amount)
	:ItemInstance(itemData.idx, itemData.name, itemData.effect, itemData.value, itemData.price, itemData.isConsumable, itemData.isStackable, itemData.isEquipable, itemData.equipParts, amount)
{
	equipState = ItemEquipState::IES_UnEquipped;
}

EquipItem::~EquipItem()
{
}

bool EquipItem::Equip(CharacterBase* target)
{
	if (nullptr == target)
		return false;

	// 이미 장비되어 있음
	if (IsEquipped())
		return false;

	// 수리검 같은건 장비하면서도 사용할수 있으니...??
	// 일단 코드 자체는 내버려두자
	if (true == itemData.isConsumable &&
		stock < 1)
	{
		return false;
	}

	// 임시용 코드
	equipState = ItemEquipState::IED_Equipped;

	if (true == itemData.isConsumable)
	{
		stock--;
	}

	return true;
}

bool EquipItem::Unequip(CharacterBase* target)
{
	if (nullptr == target)
		return false;

	// 이미 장착 해제된 장비
	if (IsUnequipped())
		return false;

	// 임시용 코드 - 필요에 따라 코드 수정 예정
	equipState = ItemEquipState::IES_UnEquipped;

	return false;
}
