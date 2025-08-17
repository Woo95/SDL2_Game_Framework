#pragma once

#include "Component.h"
#include "../../Core/Utils/InputUtils.h"

class CInputComponent : public CComponent
{
public:
	CInputComponent();
	virtual ~CInputComponent();

private:
	// 개별 바인더들을 저장
	std::unordered_map<std::string, FBinder*> mBinders;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	// 람다, 바인드 등 std::function 타입 함수를 키에 바인딩할 때 사용
	void AddFunctionToBinder(const std::string& key, void* obj, const std::function<void()>& func)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
		{
			binder = CMemoryPoolManager::GetInst()->Allocate<FBinder>();
			mBinders[key] = binder;
		}

		FBindFunction* binderFunc = CMemoryPoolManager::GetInst()->Allocate<FBindFunction>();

		binderFunc->obj = obj;
		binderFunc->func = func;

		binder->Functions.emplace_back(binderFunc);
	}
	// 클래스 멤버 함수를 키에 바인딩할 때 사용
	template <typename T>
	void AddFunctionToBinder(const std::string& key, T* obj, void(T::* func)())
	{
		AddFunctionToBinder(key, obj, std::bind(func, obj));
	}

	void DeleteFunctionFromBinder(const std::string& key, void* obj)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
			return;

		std::vector<FBindFunction*>& functions = binder->Functions;

		for (size_t i = functions.size(); i > 0; i--)
		{
			FBindFunction* bindFunc = functions[i - 1];

			if (bindFunc->obj == obj)
			{
				std::swap(functions[i - 1], functions.back());
				functions.pop_back();

				CMemoryPoolManager::GetInst()->DeallocateButKeepPool<FBindFunction>(bindFunc);
			}
		}
	}

	// keyboard
	void AddInputToBinder(const std::string& key, SDL_Scancode keyCode, EKeyAction action)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
			return;

		binder->Keys.emplace_back(std::make_pair(keyCode, action));
	}
	// mouse
	void AddInputToBinder(const std::string& key, Uint8 button, EKeyAction action)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
			return;

		binder->Mouses.emplace_back(std::make_pair(button, action));
	}
};