#include "Player.h"
#include "../ItemInstance.h"
#include <algorithm>

Player::Player(string name, Stat stat):CharacterBase(name, stat)
{
	m_level	=	1;
	m_gold	=	1000;
	m_experience = 0;
}

bool Player::UseItem(int idx, CharacterBase* target)
{
	auto it = find_if(m_inventory.begin(), m_inventory.end(), [idx](const ItemInstance* invItem) {
		return invItem->GetItemIdx() == idx;
		});
	if (it != m_inventory.end()) {
		if ((*it)->UseItem(target)) {
			if ((*it)->GetItemStock() <= 0) {
				delete* it;
				m_inventory.erase(it);
			}
		}
		else {
			cout << "사용할 수 없는 아이템 입니다." << endl;
		}
		return true;
	}
	else {
		cout << "아이템이 없습니다." << endl;
		return false;
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
			(*it)->AddItemStock(item->GetItemStock());
		} 
		else {
			m_inventory.push_back(item);
		}

	}	
	else {
		m_inventory.push_back(item);
	} 
	cout << item->GetItemName() << "를(을) 획득하였습니다" << endl;
}

bool Player::PopItem(int idx, int stocks)
{
	auto it = find_if(m_inventory.begin(), m_inventory.end(), [idx](const ItemInstance* invItem) {
		return invItem->GetItemIdx() == idx;
		});

	if (it == m_inventory.end()) {
		cout << "ERROR : 보유한 아이템이 아닙니다.\n";
		return false;
	} 

	if ((*it)->GetItemStock() < stocks) {
		cout << "ERROR : 해당 아이템의 보유 수량이 부족합니다.\n";
		return false;
	}	
	
	// 스택어블이 아니거나 가진 수량전부 파매하는 경우 그냥 삭제
	if ((*it)->isStackableItem() == false || (*it)->GetItemStock() == stocks) {
		delete* it;
		m_inventory.erase(it);
	}
	else // 그 외에는 재고 감소 
	{
		//subtrack item stocks
	}

	return true;
	
}

void Player::ShowInventory()
{
	cout << "----- 인벤토리 -----" << endl;
	if (m_inventory.empty()) {
		cout << "인벤토리가 비어 있습니다." << endl;
	}
	else {
		for (size_t i = 0; i < m_inventory.size(); i++) {
			ItemInstance* item = m_inventory[i];
			cout << i + 1 << ". " << item->GetItemName()
				<< " (가격: " << item->GetItemPrice()
				<< ", 재고: " << (item->GetItemStock()) << ", idx: " << item->GetItemIdx() << ")"
				<< endl;
		}
	}
}

void Player::AddExp(int exp)
{

	m_experience += exp;
	cout << GetName() << "은(는) " << exp << " 경험치를 얻었습니다." << endl;

	while (m_experience >= 100) {
		m_experience -= 100;		
		if (m_level < 10) {
			m_level++;
			int hpIncrease = 20;
			int newMaxHp = GetMaxHp() + hpIncrease;
			SetMaxHp(newMaxHp);
			SetCurrentHp(newMaxHp);

			int attackIncrease = 5;
			int newAttack = GetAttack() + attackIncrease;
			SetAttack(newAttack);

			cout << GetName() << "의 레벨이 상승하였습니다." << endl << "현재 레벨: " << m_level << endl;
			cout << "최대 체력 증가, hp가 회복되었습니다. " << endl
				<< "최대 체력: " << GetMaxHp() << endl;
			cout << "공격력이 증가되었습니다. " << endl
				<< "공격력: " << GetAttack() << endl;
		}
	}

	cout << "현재 경험치: " << m_experience << " / " << m_level * 100 << endl;

}

int Player::getGold() const
{
	return this->m_gold;
}

void Player::addGold(int gold)
{
	m_gold += gold;
	cout << GetName() << "은(는) " << gold << " 골드를 얻었습니다. 현재 골드: " << m_gold << endl;
}

bool Player::useGold(int gold)
{
	if (m_gold >= gold) {
		m_gold -= gold;
		cout << GetName() << "은(는) " << gold << " 골드를 사용했습니다. 남은 골드: " << m_gold << endl;
		return true;
	}
	else {
		cout << GetName() << "의 골드가 부족합니다. 현재 골드: " << m_gold << endl;
		return false;
	}
}

void Player::DisplayStat()
{
	cout << "===== Player Status =====" << endl;
	cout << "이름  : " << GetName() << endl;
	cout << "Level : " << m_level << endl;
	cout << "HP    : " << GetCurrentHp() << " / " << GetMaxHp() << endl;
	cout << "공격력: " << GetAttack() << endl;
	cout << "경험치: " << m_experience << endl;
	cout << "골드  : " << m_gold << endl;
	
	ShowInventory();

	cout << "=========================" << endl;
}



void Player::Attack(CharacterBase* target)
{
	target->TakeDamage(GetAttack());
}

void Player::TakeDamage(int damage)
{
	int currentHp = GetCurrentHp() - damage;
	if (currentHp < 0) currentHp = 0;
	SetCurrentHp(currentHp);

	float hpRatio = (float)currentHp / (float)GetMaxHp();

	cout << GetName() << "이(가) " << damage << "만큼의 피해를 입었습니다." << endl;

	if (IsDead()) {
		cout << GetName() << "은(는) 쓰러졌습니다!" << endl;
	}
	else if (hpRatio >= 0.7f) {
		cout << "가벼운 상처에 불과합니다." << endl;
	}
	else if (hpRatio >= 0.3f) {
		cout << "상당한 피해를 입었습니다." << endl;
	}
	else {
		cout << "치명적인 피해를 입었습니다!" << endl;
	}

	cout << "남은 체력: " << currentHp << " / " << GetMaxHp() << endl;
}

bool Player::IsDead()
{
	return (GetCurrentHp() <= 0);
}
