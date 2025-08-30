#pragma once

#include "../Core/Utils/InputUtils.h"
#include "../Core/Vector2D.h"

class CInputManager
{
	friend class CEngine;

private:
	CInputManager();
	~CInputManager();

private:
	static CInputManager* mInst;

	// 사용될 모든 키보드 (입력값 + 입력상태)를 묶어서 저장
	std::unordered_map<SDL_Scancode, FKeyState> mKeys;

	// 사용될 모든 마우스 (입력값 + 입력상태)를 묶어서 저장
	std::unordered_map<Uint8, FKeyState> mMouses;
	FVector2D mMousePos = FVector2D::ZERO;

private:
	bool Init();
	bool RegisterKey(SDL_Scancode keyCode);
	bool RegisterMouse(Uint8 button);

	void Update();
	void UpdateInputState();
	void HandleInputState(bool& press, bool& hold, bool& release, bool isPressed);

public:
	bool GetKeyState(SDL_Scancode keyCode, EKeyAction action)
	{
		switch (action)
		{
		case EKeyAction::PRESS:
			return mKeys[keyCode].Press;
		case EKeyAction::HOLD:
			return mKeys[keyCode].Hold;
		case EKeyAction::RELEASE:
			return mKeys[keyCode].Release;
		default:
			return false;
		}
	}
	bool GetMouseButtonState(Uint8 button, EKeyAction action)
	{
		switch (action)
		{
			case EKeyAction::PRESS:
				return mMouses[button].Press;
			case EKeyAction::HOLD:
				return mMouses[button].Hold;
			case EKeyAction::RELEASE:
				return mMouses[button].Release;
			default:
				return false;
		}
	}
	const FVector2D& GetMousePos() const { return mMousePos; }

public:
	static CInputManager* GetInst()
	{
		if (!mInst)
			mInst = new CInputManager;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};