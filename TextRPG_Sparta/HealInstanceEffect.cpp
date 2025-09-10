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
	
	int targetResultHp = targetCurrentHp + effectContext.value;
	int HealAmount = (targetResultHp < targetMaxHp) ? effectContext.value : targetResultHp - targetMaxHp;
	targetResultHp = min(targetResultHp, targetMaxHp);

	std::cout <<  HealAmount << "만큼의 체력을 회복하였습니다!" << '\n';
	
	target->SetCurrentHp(targetResultHp);
	std::cout << "현재 체력 : " << target->GetCurrentHp() << " / " << target->GetMaxHp() << '\n';

	return true;
}