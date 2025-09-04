#pragma once

#include<functional>
#include<memory>
#include<string>

// 나중에 이거 대신 include
class CharacterBase;

struct EffectContext
{
	int value;
	CharacterBase* target;
	// 차후 필요 시, Caster 등을 추가
};

class IEffect
{
public:
	virtual bool Apply(EffectContext& effectContext) = 0;
	virtual const std::string& GetId() = 0;
};

using EffectFactory = std::function<std::unique_ptr<IEffect>()>;