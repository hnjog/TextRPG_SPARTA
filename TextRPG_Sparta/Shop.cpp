#include "Shop.h"

Shop::Shop(int shopID)
{
	this->shopID = shopID;
}

void Shop::AddItem(int itemID, int count)
{
	if (count <= 0)//1개 이상 추가 필요
		return;

	sellList[itemID] += count;
}

void Shop::AddItemRange(vector<int> itemIDList, vector<int> countList)
{
	int length = itemIDList.size();

	//두 vector의 길이가 서로 불일치
	if (length == 0 || length != countList.size())
		return;

	for (int iNum = 0; iNum < length; iNum++)
	{
		if (countList[iNum] <= 0)//1개 이상 추가 필요
			continue;

		sellList[itemIDList[iNum]] += countList[iNum];
	}
}

bool Shop::RemoveItem(int itemID, int count)
{
	//판매중인 아이템이 아님
	if (sellList.find(itemID) == sellList.end())
		return false;

	//1개 이상 제거 필요
	if (count <= 0)
		return false;

	//개수 부족
	if (sellList[itemID] < count)
		return false;

	//제거 성공
	sellList[itemID] -= count;
	return true;
}
