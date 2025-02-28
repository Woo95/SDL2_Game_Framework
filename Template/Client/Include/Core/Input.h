#pragma once

#include "Utils/InputUtils.h"
#include "Vector2D.h"
#include "../Manager/MemoryPoolManager.h"

class CInput
{
	friend class CGameManager;

private:
	CInput();
	~CInput();

private:
	// 사용될 모든 키보드 (입력 값 + 상태)를 묶어서 저장
	std::unordered_map<SDL_Scancode, FInputState> mKeys;

	// 사용될 모든 마우스 (입력 값 + 상태)를 묶어서 저장
	std::unordered_map<Uint8, FInputState> mMouses;
	FVector2D mMousePos = FVector2D::ZERO;

	// 개별 바인더들을 저장
	std::unordered_map<std::string, FBinder*> mBinders;

private:
	static CInput* mInst;

private:
	bool Init();
	void Update();

	void UpdateInput();
	void HandleInputState(bool& press, bool& hold, bool& release, bool isPressed);

	void HandleBinderFuncs();
	bool VerifyState(EKey::State state, const FInputState& inputState);

	// 사용할 키보드/마우스 조작키를 미리 생성
	bool CreateKey(SDL_Scancode keyCode);
	bool CreateMouse(Uint8 button);

public:
	bool GetMouseButtonState(Uint8 button, EKey::State state)
	{
		switch (state)
		{
			case EKey::State::PRESS:
				return mMouses[button].Press;
			case EKey::State::HOLD:
				return mMouses[button].Hold;
			case EKey::State::RELEASE:
				return mMouses[button].Release;
			default:
				return false;
		}
	}
	const FVector2D& GetMousePos() const { return mMousePos; }

public:
	template <typename T>
	void AddFunctionToBinder(const std::string& key, T* obj, void(T::* func)(), CScene* scene)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
		{
			binder = CMemoryPoolManager::GetInst()->Allocate<FBinder>();
			mBinders[key] = binder;
		}

		FBindFunction* binderFunc = CMemoryPoolManager::GetInst()->Allocate<FBindFunction>();
		
		binderFunc->scene = scene;
		binderFunc->obj   = obj;
		binderFunc->func  = std::bind(func, obj);

		binder->Functions.emplace_back(binderFunc);
	}

	template <typename T>
	void DeleteFunctionFromBinder(const std::string& key, T* obj)
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

				CMemoryPoolManager::GetInst()->DeallocateKeepPool<FBindFunction>(bindFunc);
			}
		}
	}

	void AddInputToBinder(const std::string& key, SDL_Scancode keyCode, EKey::State state)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
			return;

		binder->Keys.emplace_back(std::make_pair(keyCode, state));
	}
	void AddInputToBinder(const std::string& key, Uint8 button, EKey::State state)
	{
		FBinder* binder = mBinders[key];

		if (!binder)
			return;

		binder->Mouses.emplace_back(std::make_pair(button, state));
	}

public:
	static CInput* GetInst()
	{
		if (!mInst)
			mInst = new CInput;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};