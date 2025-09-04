#include "IncreaseAttackEffect.h"

std::string IncreaseAttackEffect::GetId()
{
	return "IncreaseAttack";
}

bool IncreaseAttackEffect::Apply(EffectContext& effectContext)
{
	// 공격력 증가 코드
	// 
	// (차후 장비 / 버프형 공격력 증가 생성시,
	// EffectContext 등에 Trigger를 넣어 Equip/Unequip,
	// Buf 등을 추가)
	// 
	// CharacterBase* Target = effectContext.target;
	// Target->IncreateAttack(effectContext.value);
	//

	return true;
}