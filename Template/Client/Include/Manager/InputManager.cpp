#include "InputManager.h"

CInputManager* CInputManager::mInst = nullptr;

CInputManager::CInputManager()
{
}

CInputManager::~CInputManager()
{
}

// Init에서 RegisterKey/Mouse로 입력값 등록, 오브젝트에서 콜백 추가 관리
bool CInputManager::Init()
{
	// SAMPLES //
	RegisterKey(SDL_SCANCODE_W);
	RegisterKey(SDL_SCANCODE_A);
	RegisterKey(SDL_SCANCODE_S);
	RegisterKey(SDL_SCANCODE_D);

	// SAMPLES //
	RegisterMouse(SDL_BUTTON_LEFT);
	RegisterMouse(SDL_BUTTON_RIGHT);

	return true;
}

bool CInputManager::RegisterKey(SDL_Scancode keyCode)
{
	if (mKeys.find(keyCode) != mKeys.end())
		return false;

	FKeyState state;
	mKeys[keyCode] = state;

	return true;
}

bool CInputManager::RegisterMouse(Uint8 button)
{
	if (mMouses.find(button) != mMouses.end())
		return false;

	FKeyState state;
	mMouses[button] = state;

	return true;
}

void CInputManager::Update()
{
	UpdateInputState();
}

// 실시간 키보드 및 마우스 입력값 감지
void CInputManager::UpdateInputState()
{
	// FOR KEYBOARD //
	{
		//SDL 키보드 상태를 나타내는 배열을 가져와 KeyState 포인터가 이를 가리킨다.
		//배열의 각 요소는 키의 상태를 나타내며, 0은 안 눌림, 1은 눌림을 의미한다.
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		std::unordered_map<SDL_Scancode, FKeyState>::iterator iter = mKeys.begin();
		std::unordered_map<SDL_Scancode, FKeyState>::iterator iterEnd = mKeys.end();

		for (; iter != iterEnd; iter++)
		{
			bool isPressed = keyboardState[iter->first];
			FKeyState& key = iter->second;

			HandleInputState(key.Press, key.Hold, key.Release, isPressed);
		}
	}

	// FOR MOUSE //
	{
		int mouseX, mouseY;
		// mouseState의 각 비트는 특정 마우스 버튼의 상태를 나타내며, 1은 눌림, 0은 안 눌림을 의미한다.
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

		mMousePos = { (float)mouseX, (float)mouseY };

		std::unordered_map<Uint8, FKeyState>::iterator iter = mMouses.begin();
		std::unordered_map<Uint8, FKeyState>::iterator iterEnd = mMouses.end();

		for (; iter != iterEnd; iter++)
		{
			bool isPressed = mouseState & SDL_BUTTON(iter->first);
			FKeyState& mouse = iter->second;

			HandleInputState(mouse.Press, mouse.Hold, mouse.Release, isPressed);
		}
	}
}

// 실시간 키보드 및 마우스 입력값 정보 업데이트
void CInputManager::HandleInputState(bool& press, bool& hold, bool& release, bool isPressed)
{
	if (isPressed)
	{
		if (!hold) // press 처음 누르기 시작한 상태.
		{
			press = true;
			hold  = true;
		}
		else // hold 하는 중. 이전 프레임에 누른 상태.
			press = false;
	}
	else
	{
		if (hold) // 지금 막 hold에서 press를 뗀 상태.
		{
			press   = false;
			hold    = false;
			release = true;
		}
		else if (release) // 이전 프레임에 release를 한 상태.
			release = false;
	}
}