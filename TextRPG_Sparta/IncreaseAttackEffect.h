#pragma once
#include "EffectDescriptor.h"

class IncreaseAttackEffect : public IEffect
{
	std::string GetId() override;
	bool Apply(EffectContext& effectContext) override;
};