#include "EffectManager.h"

EffectManager& EffectManager::GetInstance()
{
	static EffectManager inst;
	return inst;
}

void EffectManager::Register(std::string&& id, EffectFactory& ef)
{
	// id는 Effect 내부에서 저장할 거 아니니 Move로 뺏어 사용
	// ef는 람다 함수이기에 빼다 사용
	effectMap.emplace(std::move(id), std::move(ef));
}

std::unique_ptr<IEffect> EffectManager::Create(const std::string& id) const
{
	auto it = effectMap.find(id);

	if (it == effectMap.end())
		return nullptr;

	return it->second();
}

EffectManager::EffectManager()
{
	effectMap.reserve(32);
}