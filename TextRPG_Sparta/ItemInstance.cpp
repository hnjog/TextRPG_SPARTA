#include "ItemInstance.h"
#include "EffectManager.h"
#include "EffectDescriptor.h"
#include"Character/CharacterBase.h"
#include<memory>
#include<iostream>

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

	if (true == itemData.isStackable)
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
	if (nullptr == target)
	{
		std::cout << "아이템 사용 대상이 존재하지 않습니다!" << '\n';
		return false;
	}

	if (true == itemData.isConsumable&&
		stock < 1)
	{
		std::cout << "아이템 개수가 모자랍니다!" << '\n';
		return false;
	}

	EffectManager& effectManager = EffectManager::GetInstance();
	EffectContext context;
	context.target = target;
	context.value = itemData.value;

	std::unique_ptr<IEffect> effect = effectManager.Create(itemData.effect);
	// 없는 effect
	if (nullptr == effect)
		return false;

	if (true == effect->Apply(context))
	{
		std::cout << itemData.name << "의 사용에 성공하였습니다!" << '\n';
		if (true == itemData.isConsumable)
		{
			stock--;
			std::cout << itemData.name << "의 남은 개수 : " << stock << '\n';
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

bool ItemInstance::removeItemStock(int count)
{
	// 음수로 제거하는 것은 의도되지 않았습니다
	if (count <= 0)
		return false;

	// 이미 stock이 0이하
	if (stock <= 0)
		return false;

	stock -= count;

	// Stock이 음수가 되면 안되므로
	if (stock < 0)
		stock = 0;

	return true;
}