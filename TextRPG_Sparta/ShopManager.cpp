#include <iostream>

#include "ShopManager.h"
#include "ItemManager.h"

#include "Character/Player.h"

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
	cout << "구매할 아이템 번호를 입력하세요: ";
	cin >> opt;
	cout << "구매할 아이템 개수를 입력하세요: ";
	cin >> cnt;

	// 구매하고자 하는 아이템 금액 계산
	auto price = this->shop.CheckPrice(opt, cnt);
	
	if (price == 0) {
		// ShopBase 자체 예외처리
		return;
	}

	// 플레이어 돈 보유량 확인
	if (player->getGold() < price)
	{
		cout << "보유한 골드가 부족하여 아이템을 구매할 수 없습니다.\n";
		return;
	}

	auto receipt = shop.SellItem(opt, cnt);

#if DEV
	auto itemData = ItemManager::GetInstance().GetItemData(receipt.idx);
	cout << itemData->name << "을(를) " << cnt << "개 구매하였습니다.\n";
#endif

	auto item = ItemManager::GetInstance().MakeItem(opt, cnt);
	player->GetItem(item);
}
