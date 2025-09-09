#include <iostream>

#include "ShopManager.h"
#include "ItemManager.h"

#include "Character/Player.h"
#include "ItemInstance.h"

ShopManager& ShopManager::Instance()
{
	static ShopManager instance;
	return instance;
}

void ShopManager::InitShop()
{
	auto ItemTypeCount = ItemManager::GetInstance().GetItemTypeCount();
	for (auto i = 1; i <= ItemTypeCount; i++)
	{
		shop.AddItem(i, 5);
	}

#if DEV
	shop.PrintSellingItems();
#endif
}

/// <summary>
/// Player가 가진돈보다 CheckPrice만큼의 비용이 있으면 Player.UseGold
/// 없으면 구매불가
/// </summary>
void ShopManager::VisitShop(Player* player)
{
	this->shop.PrintSellingItems();

	int opt, cnt;
	cout << "구매할 아이템 번호를 입력하세요(나가기 -1): ";
	cin >> opt;
	if (opt == -1) return;

	cout << "구매할 아이템 개수를 입력하세요: ";
	cin >> cnt;

	// Check total price
	auto price = this->shop.CheckPrice(opt, cnt);
	
	if (price == -1) {
		// ShopBase 자체 예외처리
		return;
	}

	// Check player gold
	if (player->getGold() < price)
	{
		cout << "보유한 골드가 부족하여 아이템을 구매할 수 없습니다.\n";
		return;
	}

	auto receipt = shop.SellItem(opt, cnt);
	

#if DEV
	auto itemData = ItemManager::GetInstance().GetItemData(receipt.idx);
	cout << itemData->name << "를(을) " << cnt << "개 구매하였습니다.\n";
#endif

	// Add item && Use Gold
	auto item = ItemManager::GetInstance().MakeItem(opt, cnt);
	player->GetItem(item);
	player->useGold(price);
}
