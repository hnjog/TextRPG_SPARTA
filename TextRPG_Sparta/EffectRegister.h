#pragma once

#include"EffectManager.h"

namespace EffectTemplate
{
	template<class T>
	void RegisterEffectType()
	{
		static_assert(std::is_base_of_v<IEffect, T>, "RegisterEffectType에 이상한 타입 집어넣지 마세요!");

		EffectManager& eManager = EffectManager::GetInstance();

		// 내부에서 move로 가져가기에 
		T temp;
		// 람다 내부에서 -> std::unique_ptr<IEffect> 로 반환 타입 명시
		eManager.Register(temp.GetId(), []() -> std::unique_ptr<IEffect> {return std::make_unique<T>();});
	}

	template<class T>
	struct EffectAutoRegister
	{
		EffectAutoRegister()
		{
			RegisterEffectType<T>();
		}
	};

#define REGISTER_EFFECT_TYPE(T) static EffectTemplate::EffectAutoRegister<T> _auto_register_##T;

};

