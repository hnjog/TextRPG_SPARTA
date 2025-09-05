#include <algorithm>
#include <iostream>
#include "Shop.h"


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
