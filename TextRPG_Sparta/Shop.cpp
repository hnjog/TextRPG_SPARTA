#include <algorithm>
#include <iostream>
#include "Shop.h"
#include "ItemManager.h"

Shop::Shop(int shopID, string shopName)
{
	id = shopID;
	name = shopName;
}

ShopMessage Shop::PrintSellingItems()
{
	if (sellList.empty())
		return ShopMessage::OTHER_ERROR;

	cout << "========================================" << endl;
	cout << "* 판매 아이템 목록" << endl;
	for (auto& sellInfo : sellList)
		cout << sellInfo.first << " : " << sellInfo.second << endl;
	
	cout << "========================================" << endl;

	return ShopMessage::OK;
}

ShopMessage Shop::AddItem(int itemID, int count)
{
	if (count <= 0)//1개 이상 추가 필요
		return ShopMessage::INCORRECT_INPUT;

	sellList[itemID] += count;

	return ShopMessage::OK;
}

ShopMessage Shop::AddItemRange(vector<int> itemIDList, vector<int> countList)
{
	int length = itemIDList.size();

	//두 vector의 길이가 서로 불일치
	if (length == 0 || length != countList.size())
		return ShopMessage::INCORRECT_INPUT;

	//countList중 0이하로 입력된 값이 있음
	if (any_of(countList.begin(), countList.end(), [](int count) { return count <= 0; }))
		return ShopMessage::INCORRECT_INPUT;

	for (int& count : countList)
	{
		if (count <= 0)
			return ShopMessage::INCORRECT_INPUT;
	}

	//지정한 아이템을 해당 개수만큼 추가
	for (int iNum = 0; iNum < length; iNum++)
	{
		sellList[itemIDList[iNum]] += countList[iNum];
	}

	return ShopMessage::OK;
}

ShopMessage Shop::RemoveItem(int itemID, int count)
{
	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
		return ShopMessage::NO_SELLING_ITEM;

	//1개 이상 제거 필요
	if (count <= 0)
		return ShopMessage::INCORRECT_INPUT;

	//개수 부족
	if (sellList[itemID] < count)
		return ShopMessage::NOT_ENOUGH_STOCK;

	//제거 성공
	sellList[itemID] -= count;
	return ShopMessage::OK;
}

ShopMessage Shop::CheckPrice(_Out_ int* price, int itemID, int count)
{
	//price는 null이면 안됨
	if (price == nullptr)
		return ShopMessage::OTHER_ERROR;

	price = 0;

	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(itemID);
	if (itemData == nullptr)
		return ShopMessage::INCORRECT_ITEM;

	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
		return ShopMessage::NO_SELLING_ITEM;

	//구매하려는 개수가 0 이하
	if (count <= 0)
		return ShopMessage::INCORRECT_INPUT;

	//구매하려는 개수가 재고보다 많음
	if (sellList[itemID] < count)
		return ShopMessage::NOT_ENOUGH_STOCK;

	//가격 계산
	*price = itemData->price * count;
	return ShopMessage::OK;
}

ShopMessage Shop::SellItem(_Out_ ItemData* sellItem, int itemID, int count = 1)
{
	sellItem = nullptr;

	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(itemID);
	if (itemData == nullptr)
		return ShopMessage::INCORRECT_ITEM;

	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
		return ShopMessage::NO_SELLING_ITEM;

	//구매하려는 개수가 0 이하
	if (count <= 0)
		return ShopMessage::INCORRECT_INPUT;

	//구매하려는 개수가 재고보다 많음
	if (sellList[itemID] < count)
		return ShopMessage::NOT_ENOUGH_STOCK;

	//판매 처리
	sellList[itemID] -= count;
	sellItem = nullptr;//TODO : 올바른 아이템 데이터를 반환해야함

	return ShopMessage::OK;
}
