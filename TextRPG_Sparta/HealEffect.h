#pragma once

#include "EffectDescriptor.h"

class HealEffect : public IEffect
{
	std::string GetId() override;
	bool Apply(EffectContext& effectContext) override;
};