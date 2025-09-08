#include <algorithm>
#include <iostream>
#include "ShopBase.h"
#include "ItemManager.h"

ShopBase::ShopBase(int shopID, string shopName)
{
	id = shopID;
	name = shopName;
}

void ShopBase::PrintSellingItems()
{
	if (sellList.empty())
	{
		cout << "ERROR : 판매중인 아이템이 없습니다." << endl;
		return;
	}

	cout << "========================================" << endl;
	cout << "* 판매 아이템 목록" << endl;
	for (auto& sellInfo : sellList)
		cout << sellInfo.first << " : " << sellInfo.second << endl;
	
	cout << "========================================" << endl;
}

bool ShopBase::AddItem(int itemID, int count)
{
	if (count <= 0)//1개 이상 추가 필요
	{
		cout << "ERROR : 추가할 개수가 0 이하입니다." << endl;
		return false;
	}

	sellList[itemID] += count;

	return true;
}

bool ShopBase::AddItemRange(vector<int> itemIDList, vector<int> countList)
{
	int length = itemIDList.size();

	//두 vector의 길이가 서로 불일치
	if (length == 0 || length != countList.size())
	{
		cout << "ERROR : itemIDList와 countList의 size가 0이거나 불일치합니다." << endl;
		return false;
	}

	//countList중 0이하로 입력된 값이 있음
	if (any_of(countList.begin(), countList.end(), [](int count) { return count <= 0; }))
	{
		cout << "ERROR : 추가할 개수가 0 이하인 값이 있습니다." << endl;
		return false;
	}

	//지정한 아이템을 해당 개수만큼 추가
	for (int iNum = 0; iNum < length; iNum++)
	{
		sellList[itemIDList[iNum]] += countList[iNum];
	}

	return true;
}

bool ShopBase::RemoveItem(int itemID, int count)
{
	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
	{
		cout << "ERROR : 판매중인 아이템이 아닙니다." << endl;
		return false;
	}

	//1개 이상 제거 필요
	if (count <= 0)
	{
		cout << "ERROR : 제거할 개수가 0 이하입니다." << endl;
		return false;
	}

	//개수 부족
	if (sellList[itemID] < count)
	{
		cout << "ERROR : 제거할 개수가 판매중인 개수보다 많습니다." << endl;
		return false;
	}

	//제거 성공
	sellList[itemID] -= count;
	return false;
}

int ShopBase::CheckPrice(int itemID, int count)
{
	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(itemID);
	if (itemData == nullptr)
	{
		cout << "ERROR : 아이템 번호를 확인해주세요." << endl;
		return 0;
	}

	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
	{
		cout << "ERROR : 판매중인 아이템이 아닙니다." << endl;
		return 0;
	}

	//구매하려는 개수가 0 이하
	if (count <= 0)
	{
		cout << "ERROR : 구매할 개수가 0 이하입니다." << endl;
		return 0;
	}

	//구매하려는 개수가 재고보다 많음
	if (sellList[itemID] < count)
	{
		cout << "ERROR : 구매할 개수가 판매중인 개수보다 많습니다." << endl;
		return 0;
	}

	//가격 계산하고 반환
	return itemData->price * count;
}

ItemData* ShopBase::SellItem(int itemID, int count)
{
	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(itemID);
	if (itemData == nullptr)
	{
		cout << "ERROR : 아이템 번호를 확인해주세요." << endl;
		return nullptr;
	}

	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
	{
		cout << "ERROR : 판매중인 아이템이 아닙니다." << endl;
		return nullptr;
	}

	//구매하려는 개수가 0 이하
	if (count <= 0)
	{
		cout << "ERROR : 구매할 개수가 0 이하입니다." << endl;
		return nullptr;
	}

	//구매하려는 개수가 재고보다 많음
	if (sellList[itemID] < count)
	{
		cout << "ERROR : 구매할 개수가 판매중인 개수보다 많습니다." << endl;
		return nullptr;
	}

	//판매 처리
	//TODO : 올바른 데이터를 반환하도록 변경
	sellList[itemID] -= count;
	//ItemData* sellItemData(itemData);
	//return sellItemData;
	return nullptr;
}
