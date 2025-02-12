#include "Input.h"

CInput* CInput::mInst = nullptr;

CInput::CInput()
{
}

CInput::~CInput()
{
	// 이 코드블럭 안의 지역변수는 여기에서만 메모리가 유지된다.
	{
		std::unordered_map<SDL_Scancode, FKey*>::iterator iter1    = mKeys.begin();
		std::unordered_map<SDL_Scancode, FKey*>::iterator iter1End = mKeys.end();

		for (; iter1 != iter1End; iter1++)
		{
			FKey* key = iter1->second;

			for (int state = 0; state < EKey::State::MAX; state++)
			{
				std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iter2    = key->Actions[state].begin();
				std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iter2End = key->Actions[state].end();

				for (; iter2 != iter2End; iter2++)
				{
					std::vector<FBindFunction*>& bindFuncs = iter2->second;

					for (FBindFunction* func : bindFuncs)
					{
						SAFE_DELETE(func);
					}
				}
			}
			SAFE_DELETE(key);
		}
		mKeys.clear();
	}
	// 이 코드블럭 안의 지역변수는 여기에서만 메모리가 유지된다.
	{
		std::unordered_map<Uint8, FMouse*>::iterator iter1    = mMouses.begin();
		std::unordered_map<Uint8, FMouse*>::iterator iter1End = mMouses.end();

		for (; iter1 != iter1End; iter1++)
		{
			FMouse* mouse = iter1->second;

			for (int state = 0; state < EKey::State::MAX; state++)
			{
				std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iter2    = mouse->Actions[state].begin();
				std::map<std::tuple<bool, bool, bool>, std::vector<FBindFunction*>>::iterator iter2End = mouse->Actions[state].end();

				for (; iter2 != iter2End; iter2++)
				{
					std::vector<FBindFunction*>& bindFuncs = iter2->second;

					for (FBindFunction* func : bindFuncs)
					{
						SAFE_DELETE(func);
					}
				}
			}
			SAFE_DELETE(mouse);
		}
		mMouses.clear();
	}
}

// CreateKey()와 CreateMouse()를 통해 모든 키보드/마우스 입력 값을 CInput::Init()에서 등록한다.
// 각 오브젝트 클래스에서 입력 값에 호출 할 함수를 추가 및 수정한다.
bool CInput::Init()
{
	CreateKey(SDL_SCANCODE_W);
	CreateKey(SDL_SCANCODE_A);
	CreateKey(SDL_SCANCODE_S);
	CreateKey(SDL_SCANCODE_D);

	CreateMouse(SDL_BUTTON_LEFT);
	CreateMouse(SDL_BUTTON_RIGHT);

	return true;
}

void CInput::Update()
{
	UpdateInput();

	UpdateBindFunction();
}

// 실시간 마우스 및 키보드 입력을 감지 및 업데이트
void CInput::UpdateInput()
{
	// FOR KEYBOARD //
	{
		//SDL 키보드 상태를 나타내는 배열을 가져와 KeyState 포인터가 이를 가리킨다.
		//배열의 각 요소는 키의 상태를 나타내며, 0은 안 눌림, 1은 눌림을 의미한다.
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		mCtrl  = keyboardState[SDL_SCANCODE_LCTRL];
		mAlt   = keyboardState[SDL_SCANCODE_LALT];
		mShift = keyboardState[SDL_SCANCODE_LSHIFT];

		std::unordered_map<SDL_Scancode, FKey*>::iterator iter    = mKeys.begin();
		std::unordered_map<SDL_Scancode, FKey*>::iterator iterEnd = mKeys.end();

		for (; iter != iterEnd; iter++)
		{
			bool isPressed = keyboardState[iter->first];
			FKey* key = iter->second;

			HandleInputState(key->Press, key->Hold, key->Release, isPressed);
		}
	}
	//// FOR MOUSE //
	{
		int mouseX, mouseY;
		// mouseState의 각 비트는 특정 마우스 버튼의 상태를 나타내며, 1은 눌림, 0은 안 눌림을 의미한다.
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

		mMousePos = { (float)mouseX, (float)mouseY };

		std::unordered_map<Uint8, FMouse*>::iterator iter    = mMouses.begin();
		std::unordered_map<Uint8, FMouse*>::iterator iterEnd = mMouses.end();

		for (; iter != iterEnd; iter++)
		{
			bool isPressed = mouseState & SDL_BUTTON(iter->first);
			FMouse* mouse = iter->second;

			HandleInputState(mouse->Press, mouse->Hold, mouse->Release, isPressed);
		}
	}
}

void CInput::HandleInputState(bool& press, bool& hold, bool& release, bool isPressed)
{
	if (isPressed)
	{
		if (!hold) // 처음 누르기 시작한 단계.
		{
			press = true;
			hold  = true;
		}
		else // 이전 프레임에 누른 상태, 현재도 누르고 있다는 의미
		{
			press = false;
		}
	}
	else if (hold) // 키를 현재 누른 상태가 아니다. 즉, 지금 막 떼었다는 의미
	{
		press   = false;
		hold    = false;
		release = true;
	}
	else if (release) // Release가 true라는 뜻은, "이전 프레임에 Release를 했다는 의미". 즉, 이제는 Release도 아니다.
	{
		release = false;
	}
}

// 등록된 입력 정보를 비교하여, 해당 입력 상태에 따라 등록된 함수들을 호출
void CInput::UpdateBindFunction()
{
	std::tuple<bool, bool, bool> modifierKeys = std::make_tuple(mCtrl, mAlt, mShift);

	// For KEYBOARD
	{
		std::unordered_map<SDL_Scancode, FKey*>::iterator iter    = mKeys.begin();
		std::unordered_map<SDL_Scancode, FKey*>::iterator iterEnd = mKeys.end();

		for (; iter != iterEnd; iter++)
		{
			FKey* key = iter->second;

			if (key->Press)   ExecuteBindFunctions(modifierKeys, key, EKey::State::Press,   EInput::Type::KEYBOARD);
			if (key->Hold)    ExecuteBindFunctions(modifierKeys, key, EKey::State::Hold,    EInput::Type::KEYBOARD);
			if (key->Release) ExecuteBindFunctions(modifierKeys, key, EKey::State::Release, EInput::Type::KEYBOARD);
		}
	}
	// FOR MOUSE
	{
		std::unordered_map<Uint8, FMouse*>::iterator iter    = mMouses.begin();
		std::unordered_map<Uint8, FMouse*>::iterator iterEnd = mMouses.end();

		for (; iter != iterEnd; iter++)
		{
			FMouse* mouse = iter->second;

			if (mouse->Press)   ExecuteBindFunctions(modifierKeys, mouse, EKey::State::Press,   EInput::Type::MOUSE);
			if (mouse->Hold)    ExecuteBindFunctions(modifierKeys, mouse, EKey::State::Hold,    EInput::Type::MOUSE);
			if (mouse->Release) ExecuteBindFunctions(modifierKeys, mouse, EKey::State::Release, EInput::Type::MOUSE);
		}
	}
}

void CInput::ExecuteBindFunctions(std::tuple<bool, bool, bool>& modifierKeys, void* input, EKey::State state, EInput::Type type)
{
	switch (type)
	{
		case EInput::Type::KEYBOARD:
		{
			FKey* key = (FKey*)input;

			if (key->Actions[state].find(modifierKeys) != key->Actions[state].end()) // if found
			{
				std::vector<FBindFunction*>& bindFunctions = key->Actions[state][modifierKeys];

				for (FBindFunction* bindFunc : bindFunctions)
					bindFunc->func();
			}
		}
		break;

		case EInput::Type::MOUSE:
		{
			FMouse* mouse = (FMouse*)input;

			if (mouse->Actions[state].find(modifierKeys) != mouse->Actions[state].end()) // if found
			{
				std::vector<FBindFunction*>& bindFunctions = mouse->Actions[state][modifierKeys];

				for (FBindFunction* bindFunc : bindFunctions)
					bindFunc->func();
			}
		}
		break;
	}
}

bool CInput::CreateKey(SDL_Scancode keyCode)
{
	if (mKeys.find(keyCode) != mKeys.end())
		return false;

	FKey* key = new FKey;
	mKeys[keyCode] = key;

	return true;
}

bool CInput::CreateMouse(Uint8 button)
{
	if (mMouses.find(button) != mMouses.end())
		return false;

	FMouse* mouse = new FMouse;
	mMouses[button] = mouse;

	return true;
}