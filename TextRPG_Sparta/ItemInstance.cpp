#include "ItemInstance.h"
#include "EffectManager.h"
#include "EffectDescriptor.h"
#include<memory>

ItemInstance::ItemInstance()
	:stock(0)
{
}

ItemInstance::ItemInstance(int idx, const std::string& name, const std::string& effect, int value, int price, bool isConsumable, bool isStackable, int amount)
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

ItemInstance::ItemInstance(const ItemData& itemData, int amount)
	:ItemInstance(itemData.idx,itemData.name,itemData.effect,itemData.value,itemData.price,itemData.isConsumable,itemData.isStackable,amount)
{
}

bool ItemInstance::UseItem(CharacterBase* target)
{
	if (target == nullptr)
		return false;

	if (true == itemData.isConsumable&&
		stock < 1)
	{
		return false;
	}

	EffectManager& effectManager = EffectManager::GetInstance();
	EffectContext context;
	context.target = target;
	context.value = itemData.value;

	std::unique_ptr<IEffect> effect = effectManager.Create(itemData.effect);
	// 없는 effect
	if (effect == nullptr)
		return false;

	if (effect->Apply(context))
	{
		if (true == itemData.isConsumable)
		{
			stock--;
		}

		return true;
	}

	return false;
}

bool ItemInstance::AddItemStock(int count)
{
	if (count <= 0)
		return false;

	// 여러 개 들고 다닐 수 없는데 이미 1개 들고 있다
	if (false == itemData.isStackable &&
		stock >= 1)
	{
		return false;
	}

	stock += count;
	return true;
}
