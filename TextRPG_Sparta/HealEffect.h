#pragma once

#include "EffectDescriptor.h"

class HealEffect : public IEffect
{
	const std::string& GetId() override;
	bool Apply(EffectContext& effectContext) override;
};

