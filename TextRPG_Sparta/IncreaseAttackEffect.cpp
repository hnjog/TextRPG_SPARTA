#include "IncreaseAttackEffect.h"
#include"Character/CharacterBase.h"

std::string IncreaseAttackEffect::GetId()
{
	return "IncreaseAttack";
}

bool IncreaseAttackEffect::Apply(EffectContext& effectContext)
{
	CharacterBase* target = effectContext.target;
	if (nullptr == target)
		return false;

	if (effectContext.value < 0)
		return false;

	int targetAttack = target->GetAttack();
	int AttackAmount = targetAttack + effectContext.value;
	std::cout << effectContext.value << "만큼 공격력이 증가하였습니다" << '\n';
	target->SetAttack(AttackAmount);
	std::cout << "현재 공격력 : " << target->GetAttack() << '\n';

	return true;
}