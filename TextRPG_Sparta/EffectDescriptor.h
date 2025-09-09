#pragma once

#include<functional>
#include<memory>
#include<string>

#include"Character/CharacterBase.h"

enum class EffectTrigger
{
	EFT_USE = 0,
	EFT_EQUIP,
	EFT_UNEQUIP,
};

struct EffectContext
{
	int value;
	CharacterBase* target;
	// 차후 필요 시, Caster 등을 추가
	EffectTrigger trigger;
};

class IEffect
{
public:
	virtual bool Apply(EffectContext& effectContext) = 0;
	virtual std::string GetId() = 0;
};

using EffectFactory = std::function<std::unique_ptr<IEffect>()>;