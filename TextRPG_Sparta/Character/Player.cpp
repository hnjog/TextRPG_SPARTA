#include "Player.h"
#include "../ItemInstance.h"
#include <algorithm>

Player::Player(string name, Stat stat):CharacterBase(name, stat)
{
	m_level = 0;
	m_gold = 0;
	m_experience = 0;
}

bool Player::UseItem(int idx, CharacterBase* target)
{
	auto it = find_if(m_inventory.begin(), m_inventory.end(), [idx](const ItemInstance* invItem) {
		return invItem->GetItemIdx() == idx;
		});
	if (it != m_inventory.end()) {
		(*it)->UseItem(target);
	}
	else {
		cout << "아이템이 없습니다." << endl;
	}
	return false;
}

void Player::GetItem(ItemInstance* item)
{
	if (item->isStackableItem()) {
		auto it = find_if(m_inventory.begin(),m_inventory.end(), [item](const ItemInstance* invItem) {
			return invItem->GetItemIdx() == item->GetItemIdx();
			});
		if (it != m_inventory.end()) {
			//(*it)->stock++;
		}
	}	
	else {
		m_inventory.push_back(item);
		sort(m_inventory.begin(), m_inventory.end(), [](const ItemInstance* A, const ItemInstance* B) {
			return A->GetItemName() < B->GetItemName();
			});
	} 
}

void Player::DisplayStat()
{

}

void Player::TakeDamage(int damage)
{
	int currentHp = GetCurrentHp() - damage;
	if (currentHp < 0) currentHp = 0;
	SetCurrentHp(currentHp);
}

bool Player::IsDead()
{
	return (GetCurrentHp() <= 0);
}
