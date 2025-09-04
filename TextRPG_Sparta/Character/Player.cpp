#include "Player.h"

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

void Player::GetItem(int idx)
{
}

void Player::DisplayStat()
{

}

void Player::TakeDamage(int damage)
{
}

bool Player::IsDead()
{
	return false;
}
