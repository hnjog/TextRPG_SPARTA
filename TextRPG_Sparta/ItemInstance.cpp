#include "ItemInstance.h"
#include "EffectManager.h"
#include "EffectDescriptor.h"

ItemInstance::ItemInstance()
	:stock(0)
{
}

ItemInstance::ItemInstance(int idx, std::string& name, std::string& effect, int value, int price, bool isConsumable, bool isStackable, int amount)
{
	itemData.idx = idx;
	itemData.name = name;
	itemData.effect = effect;
	itemData.value = value;
	itemData.price = price;
	itemData.isConsumable = isConsumable;
	itemData.isStackable = isStackable;

	if (itemData.isStackable)
		stock = amount;
	else
		stock = 1;
}

ItemInstance::ItemInstance(ItemData& itemData, int amount)
	:ItemInstance(itemData.idx,itemData.name,itemData.effect,itemData.value,itemData.price,itemData.isConsumable,itemData.isStackable,amount)
{
}

bool ItemInstance::UseItem(CharacterBase* target)
{
	EffectManager& effectManager = EffectManager::GetInstance();
	EffectContext context;
	context.target = target;
	context.value = itemData.value;
	if (effectManager.Create(itemData.effect)->Apply(context))
	{
		if (itemData.isConsumable)
		{
			stock--;
		}

		return true;
	}

	return false;
}
