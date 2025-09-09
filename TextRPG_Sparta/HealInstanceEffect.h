#pragma once

#include "EffectDescriptor.h"
#include "EffectRegister.h"

class Heal_InstanceEffect : public IEffect
{
public:
	std::string GetId() override;
	bool Apply(EffectContext& effectContext) override;
};

REGISTER_EFFECT_TYPE(Heal_InstanceEffect)