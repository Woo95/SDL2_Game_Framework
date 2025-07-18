#pragma once

#include "Utils/InputUtils.h"
#include "Vector2D.h"

class CInput
{
	friend class CGameManager;

private:
	CInput();
	~CInput();

private:
	static CInput* mInst;

	// 사용될 모든 키보드 (입력 값 + 상태)를 묶어서 저장
	std::unordered_map<SDL_Scancode, FInputState> mKeys;

	// 사용될 모든 마우스 (입력 값 + 상태)를 묶어서 저장
	std::unordered_map<Uint8, FInputState> mMouses;
	FVector2D mMousePos = FVector2D::ZERO;

private:
	bool Init();
	bool RegisterKey(SDL_Scancode keyCode);
	bool RegisterMouse(Uint8 button);

	void Update();
	void UpdateInputState();
	void HandleInputState(bool& press, bool& hold, bool& release, bool isPressed);

public:
	bool GetKeyState(SDL_Scancode key, EKey::State state)
	{
		switch (state)
		{
		case EKey::State::PRESS:
			return mKeys[key].Press;
		case EKey::State::HOLD:
			return mKeys[key].Hold;
		case EKey::State::RELEASE:
			return mKeys[key].Release;
		default:
			return false;
		}
	}
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