#include "HealInstanceEffect.h"
#include "Character/CharacterBase.h"

std::string Heal_InstanceEffect::GetId()
{
	return "Heal_Instance";
}

bool Heal_InstanceEffect::Apply(EffectContext& effectContext)
{
	CharacterBase* target = effectContext.target;
	if (nullptr == target)
		return false;

	if (effectContext.value < 0)
		return false;

	if (effectContext.trigger != EffectTrigger::EFT_USE)
		return false;

	int targetMaxHp = target->GetMaxHp();
	int targetCurrentHp = target->GetCurrentHp();

	if (targetCurrentHp >= targetMaxHp)
		return false;

	int targetResultHp = min(targetCurrentHp + effectContext.value, targetMaxHp);
	target->SetCurrentHp(targetResultHp);

	return true;
}