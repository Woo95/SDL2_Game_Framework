#include "Input.h"

CInput* CInput::mInst = nullptr;

CInput::CInput()
{
	CMemoryPoolManager::GetInst()->CreatePool<FBinder>(20);
	CMemoryPoolManager::GetInst()->CreatePool<FBindFunction>(20);
}

CInput::~CInput()
{
	std::unordered_map<std::string, FBinder*>::iterator iter    = mBinders.begin();
	std::unordered_map<std::string, FBinder*>::iterator iterEnd = mBinders.end();

	for (; iter != iterEnd; iter++)
	{
		FBinder* binder = iter->second;

		for (FBindFunction* function : binder->Functions)
		{
			CMemoryPoolManager::GetInst()->DeallocateButKeepPool<FBindFunction>(function);
		}
		CMemoryPoolManager::GetInst()->DeallocateButKeepPool<FBinder>(binder);
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

	HandleBinderFuncs();
}

// 실시간 키보드 및 마우스 입력값 감지
void CInput::UpdateInput()
{
	// FOR KEYBOARD //
	{
		//SDL 키보드 상태를 나타내는 배열을 가져와 KeyState 포인터가 이를 가리킨다.
		//배열의 각 요소는 키의 상태를 나타내며, 0은 안 눌림, 1은 눌림을 의미한다.
		const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

		std::unordered_map<SDL_Scancode, FInputState>::iterator iter    = mKeys.begin();
		std::unordered_map<SDL_Scancode, FInputState>::iterator iterEnd = mKeys.end();

		for (; iter != iterEnd; iter++)
		{
			bool isPressed = keyboardState[iter->first];
			FInputState& key = iter->second;

			HandleInputState(key.Press, key.Hold, key.Release, isPressed);
		}
	}

	// FOR MOUSE //
	{
		int mouseX, mouseY;
		// mouseState의 각 비트는 특정 마우스 버튼의 상태를 나타내며, 1은 눌림, 0은 안 눌림을 의미한다
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

		mMousePos = { (float)mouseX, (float)mouseY };

		std::unordered_map<Uint8, FInputState>::iterator iter    = mMouses.begin();
		std::unordered_map<Uint8, FInputState>::iterator iterEnd = mMouses.end();

		for (; iter != iterEnd; iter++)
		{
			bool isPressed = mouseState & SDL_BUTTON(iter->first);
			FInputState& mouse = iter->second;

			HandleInputState(mouse.Press, mouse.Hold, mouse.Release, isPressed);
		}
	}
}

// 실시간 키보드 및 마우스 입력값 정보 업데이트
void CInput::HandleInputState(bool& press, bool& hold, bool& release, bool isPressed)
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

// 등록된 입력 정보를 비교하여, 해당 입력 상태에 따라 등록된 함수들을 호출
void CInput::HandleBinderFuncs()
{
	std::unordered_map<std::string, FBinder*>::iterator iter    = mBinders.begin();
	std::unordered_map<std::string, FBinder*>::iterator iterEnd = mBinders.end();

	for (; iter != iterEnd; iter++)
	{
		FBinder* binder = iter->second;

		if (binder->Keys.empty() && binder->Mouses.empty())
			continue;

		bool shouldExecute = true;

		// KEYBOARD //
		for (std::pair<SDL_Scancode, EKey::State>& binderKey : binder->Keys)
		{
			const SDL_Scancode& key   = binderKey.first;
			const EKey::State&  state = binderKey.second;

			std::unordered_map<SDL_Scancode, FInputState>::iterator iter = mKeys.find(key);
			if (iter == mKeys.end() || !VerifyState(state, iter->second))
			{
				shouldExecute = false;
				break;
			}
		}

		if (!shouldExecute) // 키보드에서 이미 매치되지 않기 때문에 조합이 틀리다.
			continue;

		// MOUSE //
		for (std::pair<Uint8, EKey::State>& binderMouse : binder->Mouses)
		{
			const Uint8&       mouse = binderMouse.first;
			const EKey::State& state = binderMouse.second;

			std::unordered_map<Uint8, FInputState>::iterator iter = mMouses.find(mouse);
			if (iter == mMouses.end() || !VerifyState(state, iter->second))
			{
				shouldExecute = false;
				break;
			}
		}

		if (shouldExecute)
		{
			for (FBindFunction* bindFunc : binder->Functions)
				bindFunc->func();
		}
	}
}

// 등록된 키 조합의 상태와 일치하는 입력 값의 상태를 반환
bool CInput::VerifyState(EKey::State state, const FInputState& inputState)
{
	switch (state) 
	{
		case EKey::State::PRESS:   return inputState.Press;
		case EKey::State::HOLD:    return inputState.Hold;
		case EKey::State::RELEASE: return inputState.Release;
		default:                   return false;
	}
}

bool CInput::CreateKey(SDL_Scancode keyCode)
{
	if (mKeys.find(keyCode) != mKeys.end())
		return false;

	FInputState state;
	mKeys[keyCode] = state;

	return true;
}

bool CInput::CreateMouse(Uint8 button)
{
	if (mMouses.find(button) != mMouses.end())
		return false;

	FInputState state;
	mMouses[button] = state;

	return true;
}