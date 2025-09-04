#pragma once

#include"EffectDescriptor.h"
#include<memory>
#include<string>
#include<unordered_map>

class EffectManager
{
public:
	static EffectManager& GetInstance();
	void Register(std::string&& id, EffectFactory&& ef);
	std::unique_ptr<IEffect> Create(const std::string& id) const;

private:
	EffectManager();
	std::unordered_map<std::string, EffectFactory> effectMap;
};

