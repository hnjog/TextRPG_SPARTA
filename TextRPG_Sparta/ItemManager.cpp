#include "ItemManager.h"
#include "DataManager.h"
#include <vector>
#include "ItemInstance.h"

ItemManager& ItemManager::GetInstance()
{
	static ItemManager inst;
	return inst;
}

bool ItemManager::Init()
{
	DataManager& DM = DataManager::GetInstance();
	if (DM.Initialize() == false)
		return false;

	std::vector<ItemData> itemDataVector = DM.TakeItems();
	itemMapByIdx.reserve(itemDataVector.size());

	for (const auto& itemData : itemDataVector)
	{
		itemMapByIdx[itemData.idx] = itemData;
	}

	return true;
}

void ItemManager::PrintAllItems() const
{
	for (const auto& pair : itemMapByIdx)
	{
		const ItemData& item = pair.second;
		std::cout << "==========================" << '\n';
		std::cout << "아이템 이름 : " << item.name << '\n';
		std::cout << "아이템 효과 : " << item.effect << '\n';
		std::cout << "아이템 수치 : " << item.value << '\n';
		std::cout << "아이템 인덱스 : " << item.idx << '\n';
		std::cout << "아이템 가격 : " << item.price << '\n';
		std::cout << "아이템 소모 여부 : " << item.isConsumable << '\n';
		std::cout << "아이템 스택 여부 : " << item.isStackable << '\n';
	}
}

ItemInstance* ItemManager::MakeItem(int idx, int count)
{
	if (count < 0 || idx < 0)
		return nullptr;

	auto it = itemMapByIdx.find(idx);
	if (it == itemMapByIdx.end())
		return nullptr;

	const ItemData& itemData = itemMapByIdx[idx];

	if (false == itemData.isStackable)
		count = 1;

	return new ItemInstance(itemData, count);
}

const ItemData* ItemManager::GetItemData(int idx)
{
	if (idx < 0)
		return nullptr;
	
	auto it = itemMapByIdx.find(idx);
	if (it == itemMapByIdx.end())
		return nullptr;

	return &it->second;
}
