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
		eManager.Register(T::GetId(), []() {return std::make_unique<T>(); })
	}

	template<class T>
	struct EffectAutoRegister
	{
		EffectAutoRegister()
		{
			RegisterEffectType<T>();
		}
	};

#define REGISTER_EFFECT_TYPE(T) static EffectAutoRegister<T> _auto_register_##T;
}
