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
	target->SetAttack(targetAttack + effectContext.value);
	return true;
}