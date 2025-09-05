#include "HealEffect.h"
#include "Character/CharacterBase.h"

std::string HealEffect::GetId()
{
	return "Heal";
}

bool HealEffect::Apply(EffectContext& effectContext)
{
	CharacterBase* target = effectContext.target;
	if (nullptr == target)
		return false;

	if (effectContext.value < 0)
		return false;

	int targetMaxHp = target->GetMaxHp();
	int targetCurrentHp = target->GetCurrentHp();
	int targetResultHp = min(targetCurrentHp + effectContext.value, targetMaxHp);
	target->SetCurrentHp(targetResultHp);

	return true;
}