#include "ItemManager.h"
#include "DataManager.h"

void ItemManager::Init()
{
	itemDataVector.clear();
	DataManager& DM = DataManager::Instance();
	if (DM.Initialize() == false)
		return;

	itemDataVector = DM.TakeItems();
}

void ItemManager::PrintAllItems()
{
	for (auto& item : itemDataVector)
	{
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
