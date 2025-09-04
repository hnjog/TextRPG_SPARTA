#include "HealEffect.h"

std::string HealEffect::GetId()
{
	return "Heal";
}

bool HealEffect::Apply(EffectContext& effectContext)
{
	// 체력 회복 코드
	// CharacterBase* Target = effectContext.target;
	// Target->Heal(effectContext.value);

	return true;
}