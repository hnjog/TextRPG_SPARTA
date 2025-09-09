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
	for (auto& sellInfo : sellList) {
		auto itemData = ItemManager::GetInstance().GetItemData(sellInfo.first);
		
		cout << sellInfo.first << ". " << itemData->name << " : " << itemData->price << "G(" << sellInfo.second << "개 구매가능)\n";
		//cout << sellInfo.first << " : " << sellInfo.second << endl;
	}
		
	
	cout << "========================================" << endl;
}

bool ShopBase::AddItem(int idx, int count)
{
	if (count <= 0)//1개 이상 추가 필요
	{
		cout << "ERROR : 추가할 개수가 0 이하입니다." << endl;
		return false;
	}

	sellList[idx] += count;

	return true;
}

bool ShopBase::AddItemRange(vector<int> idxList, vector<int> countList)
{
	int length = idxList.size();

	//두 vector의 길이가 서로 불일치
	if (length == 0 || length != countList.size())
	{
		cout << "ERROR : idxList와 countList의 size가 0이거나 불일치합니다." << endl;
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
		sellList[idxList[iNum]] += countList[iNum];
	}

	return true;
}

bool ShopBase::RemoveItem(int idx, int count)
{
	//판매중인 아이템이 아님
	if (sellList.find(idx) == sellList.end() || sellList[idx] == 0)
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
	if (sellList[idx] < count)
	{
		cout << "ERROR : 제거할 개수가 판매중인 개수보다 많습니다." << endl;
		return false;
	}

	//제거 성공
	sellList[idx] -= count;
	return false;
}

int ShopBase::CheckPrice(int idx, int count)
{
	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(idx);
	if (itemData == nullptr)
	{
		cout << "ERROR : 아이템 번호를 확인해주세요." << endl;
		return -1;
	}

	//판매중인 아이템이 아님
	if (sellList.find(idx) == sellList.end() || sellList[idx] == 0)
	{
		cout << "ERROR : 판매중인 아이템이 아닙니다." << endl;
		return -1;
	}

	//구매하려는 개수가 0 이하
	if (count <= 0)
	{
		cout << "ERROR : 구매할 개수가 0 이하입니다." << endl;
		return -1;
	}

	//구매하려는 개수가 재고보다 많음
	if (sellList[idx] < count)
	{
		cout << "ERROR : 구매할 개수가 판매중인 개수보다 많습니다." << endl;
		return -1;
	}

	//가격 계산하고 반환
	return itemData->price * count;
}

SellItemData ShopBase::SellItem(int idx, int count)
{
	SellItemData sellItemData;

	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(idx);
	if (itemData == nullptr)
	{
		cout << "ERROR : 아이템 번호를 확인해주세요." << endl;
		return sellItemData;
	}

	//판매중인 아이템이 아님
	if (sellList.find(idx) == sellList.end() || sellList[idx] == 0)
	{
		cout << "ERROR : 판매중인 아이템이 아닙니다." << endl;
		return sellItemData;
	}

	//구매하려는 개수가 0 이하
	if (count <= 0)
	{
		cout << "ERROR : 구매할 개수가 0 이하입니다." << endl;
		return sellItemData;
	}

	//구매하려는 개수가 재고보다 많음
	if (sellList[idx] < count)
	{
		cout << "ERROR : 구매할 개수가 판매중인 개수보다 많습니다." << endl;
		return sellItemData;
	}

	//판매 처리
	sellList[idx] -= count;

	sellItemData.idx = itemData->idx;
	sellItemData.price = itemData->price;
	sellItemData.stocks = count;
	return sellItemData;
}

int ShopBase::CheckPriceAndSellItem(SellItemData& sellItemData, int idx, int count)
{
	//올바른 아이템 번호가 아님
	const ItemData* itemData = ItemManager::GetInstance().GetItemData(idx);
	if (itemData == nullptr)
	{
		cout << "ERROR : 아이템 번호를 확인해주세요." << endl;
		return -1;
	}

	//판매중인 아이템이 아님
	if (sellList.find(idx) == sellList.end() || sellList[idx] == 0)
	{
		cout << "ERROR : 판매중인 아이템이 아닙니다." << endl;
		return -1;
	}

	//구매하려는 개수가 0 이하
	if (count <= 0)
	{
		cout << "ERROR : 구매할 개수가 0 이하입니다." << endl;
		return -1;
	}

	//구매하려는 개수가 재고보다 많음
	if (sellList[idx] < count)
	{
		cout << "ERROR : 구매할 개수가 판매중인 개수보다 많습니다." << endl;
		return -1;
	}

	//판매 처리
	sellList[idx] -= count;

	sellItemData.idx = itemData->idx;
	sellItemData.price = itemData->price;
	sellItemData.stocks = count;

	//가격 계산하고 반환
	return itemData->price * count;
}
