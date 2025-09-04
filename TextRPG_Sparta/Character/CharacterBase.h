#pragma once
#include <iostream>
 
struct Stat {
	int maxHp;
	int currentHp;
	int attack;
};

using namespace std;
class CharacterBase
{
private:
	string	m_name;
	Stat	m_baseStat;
public:
	CharacterBase() = default;
	CharacterBase(string name, Stat stat) :m_name(name), m_baseStat(stat) {}

	virtual void DisplayStat() {};
	virtual void TakeDamage(int damage) {};
	virtual bool IsDead() { return m_baseStat.currentHp <= 0; }
	//Setter
	void SetCurrentHp(int hp) { m_baseStat.currentHp = hp; };
	void SetMaxHp(int hp) { m_baseStat.maxHp = hp; };
	void SetAttack(int attack) { m_baseStat.attack = attack; };
	//Getter
	int GetCurrentHp() const { return m_baseStat.currentHp; }
	int GetMaxHp() const { return m_baseStat.maxHp; }
	int GetAttack() const { return m_baseStat.attack; }
};

