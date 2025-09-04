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
	return false;
}

void Player::GetItem(ItemInstance* item)
{
	if (item->isStackableItem()) {

	}
	m_inventory.
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
