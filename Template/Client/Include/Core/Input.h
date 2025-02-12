#pragma once

#include "InputUtils.h"
#include "Vector2D.h"

class CInput
{
	friend class CGameManager;

private:
	CInput();
	~CInput();

private:
	// KEYBOARD
	std::unordered_map<SDL_Scancode, FKey*> mKeys;
	bool mCtrl = false;
	bool mAlt = false;
	bool mShift = false;

	// MOUSE
	std::unordered_map<Uint8, FMouse*> mMouses;
	FVector2D mMousePos = FVector2D::ZERO;

private:
	static CInput* mInst;

private:
	bool Init();
	void Update();

	void UpdateInput();
	void HandleInputState(bool& press, bool& hold, bool& release, bool isPressed);

	void UpdateBindFunction();
	void ExecuteBindFunctions(std::tuple<bool, bool, bool>& modifierKeys, void* bindKey, EKey::State state, EInput::Type type);

	bool CreateKey(SDL_Scancode keyCode);
	bool CreateMouse(Uint8 button);

public:
	bool GetMouseButtonState(Uint8 button, EKey::State state)
	{
		switch (state)
		{
			case EKey::State::Press:
				return mMouses[button]->Press;
			case EKey::State::Hold:
				return mMouses[button]->Hold;
			case EKey::State::Release:
				return mMouses[button]->Release;
		}
	}
	const FVector2D& GetMousePos() const { return mMousePos; }

public:
	// !AddFunctionToKey()이 template인 이유는, 등록할 클래스의 타입을 알 수 없기 때문!
	// void (T::*func)(): "void 리턴 타입의 인자가 없는" 클래스의 멤버 함수 포인터 타입의 매개변수
	template <typename T>
	void AddFunctionToKey(bool ctrl, bool alt, bool shift, SDL_Scancode keyCode, EKey::State state, T* obj, void (T::* func)(), CScene* scene)
	{
		FKey* key = mKeys[keyCode];

		if (!key)
			return;

		FBindFunction* bindFunc = new FBindFunction;

		bindFunc->scene = scene;
		bindFunc->obj   = obj;
		bindFunc->func  = std::bind(func, obj);
#pragma region std::bind(func, obj)
		/*
			std::bind는 함수나 함수 객체를 결합하여 새로운 호출 가능한 객체를 생성하는 C++ 표준 라이브러리(functional) 기능이다.
			std::bind(func, obj)는 `obj` 객체의 `func` 멤버 함수를 결합하여 새로운 호출 객체를 만든다.
			이후 이 객체를 호출하면 `obj->func()`가 실행됩니다.
		*/
#pragma endregion

		std::tuple<bool, bool, bool> modifierKeys = std::make_tuple(ctrl, alt, shift);

		key->Actions[state][modifierKeys].emplace_back(bindFunc);
	}
	template <typename T>
	void AddFunctionToMouse(bool ctrl, bool alt, bool shift, Uint8 button, EKey::State state, T* obj, void (T::* func)(), CScene* scene)
	{
		FMouse* mouse = mMouses[button];

		if (!mouse)
			return;

		FBindFunction* bindFunc = new FBindFunction;

		bindFunc->scene = scene;
		bindFunc->obj   = obj;
		bindFunc->func  = std::bind(func, obj);

		std::tuple<bool, bool, bool> modifierKeys = std::make_tuple(ctrl, alt, shift);

		mouse->Actions[state][modifierKeys].emplace_back(bindFunc);
	}

	template <typename T>
	void DeleteFunctionFromKey(SDL_Scancode keyCode, EKey::State state, T* obj)
	{
		FKey* key = mKeys[keyCode];

		if (!key)
			return;

		std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iter    = key->Actions[state].begin();
		std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iterEnd = key->Actions[state].end();

		for (; iter != iterEnd; iter++)
		{
			std::vector<FBindFunction*>& bindFuncs = iter->second;

			for (size_t i = bindFuncs.size(); i > 0; i--)
			{
				FBindFunction* bindFunc = bindFuncs[i - 1];

				if (bindFunc->obj == obj)
				{
					std::swap(bindFuncs[i - 1], bindFuncs.back());
					bindFuncs.pop_back();

					SAFE_DELETE(bindFunc);
				}
			}
		}
	}
	template <typename T>
	void DeleteFunctionFromMouse(Uint8 button, EKey::State state, T* obj)
	{
		FMouse* mouse = mMouses[button];

		if (!mouse)
			return;

		std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iter    = mouse->Actions[state].begin();
		std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iterEnd = mouse->Actions[state].end();

		for (; iter != iterEnd; iter++)
		{
			std::vector<FBindFunction*>& bindFuncs = iter->second;

			for (size_t i = bindFuncs.size(); i > 0; i--)
			{
				FBindFunction* bindFunc = bindFuncs[i - 1];

				if (bindFunc->obj == obj)
				{
					std::swap(bindFuncs[i - 1], bindFuncs.back());
					bindFuncs.pop_back();

					SAFE_DELETE(bindFunc);
				}
			}
		}
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