#include "Input.h"

CInput* CInput::mInst = nullptr;

CInput::CInput()
{
}

CInput::~CInput()
{
	// 이 코드블럭 안의 지역변수는 여기에서만 메모리가 유지된다.
	{
		std::unordered_map<SDL_Scancode, FKeyInfo*>::iterator	iter = mMapKeyInfo.begin();
		std::unordered_map<SDL_Scancode, FKeyInfo*>::iterator	iterEnd = mMapKeyInfo.end();

#pragma region iter->
/*
			iter에서 ->는 STL에서 사용되는 객체에 대한 포인터 멤버 접근을 위한 연산자다.

			iter->는 iter 객체가 현재 저장하고 있는 "노드의 주소"를 의미한다.
			iter->second는 현재 노드가 들고있는 FKeyInfo* 변수를 의미한다.
*/
#pragma endregion
		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE(iter->second);
		}
	}

	// 이 코드블럭 안의 지역변수는 여기에서만 메모리가 유지된다.
	{
		std::unordered_map<std::string, FBindKey*>::iterator	iter = mMapBindKey.begin();
		std::unordered_map<std::string, FBindKey*>::iterator	iterEnd = mMapBindKey.end();

		for (; iter != iterEnd; ++iter)
		{
			for (int i = 0; i < EKeyType::Max; ++i)
			{
				size_t	size = iter->second->vecFunction[i].size();

				for (size_t j = 0; j < size; ++j)
				{
					SAFE_DELETE(iter->second->vecFunction[i][j]);
				}
			}
			SAFE_DELETE(iter->second);
		}
	}
}

// CreateBindKey()함수를 통해 모든 키들을 CInput::Init()에서 등록한다.
// 각 클래스에서는 AddBindFunction()를 통해 키를 눌렀을 때 작동할 함수들만 추가 및 수정한다.
bool CInput::Init()
{
	return true;
}

void CInput::Update()
{
	UpdateKeyInfo();

	UpdateBindFunction();
}

// 실시간 키 입력을 감지 및 업데이트
void CInput::UpdateKeyInfo()
{
	// SDL 키보드 상태를 나타내는 배열을 가져와 KeyState 포인터가 이를 가리킨다.
	// 배열의 각 요소는 키의 상태를 나타내며, 0은 안 눌림, 1은 눌림을 의미한다.
	const Uint8* KeyState = SDL_GetKeyboardState(nullptr);

	mCtrl	= KeyState[SDL_SCANCODE_LCTRL];
	mAlt	= KeyState[SDL_SCANCODE_LALT];
	mShift	= KeyState[SDL_SCANCODE_LSHIFT];

	std::unordered_map<SDL_Scancode, FKeyInfo*>::iterator	iter = mMapKeyInfo.begin();
	std::unordered_map<SDL_Scancode, FKeyInfo*>::iterator	iterEnd = mMapKeyInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		bool	KeyPush = false;

		if (KeyState[iter->second->Key])
		{
			KeyPush = true;
		}

		if (KeyPush)
		{
			// 처음 누르기 시작한 단계.
			if (!iter->second->Press && !iter->second->Hold)
			{
				iter->second->Press = true;
				iter->second->Hold	= true;
			}
			// 이전 프레임에 누른 상태, 현재도 누르고 있다는 의미
			else
				iter->second->Press = false;
		}
		// 키를 현재 누른 상태가 아니다. 즉, 지금 막 떼었다는 의미
		else if (iter->second->Hold)
		{
			iter->second->Press   = false;
			iter->second->Hold    = false;
			iter->second->Release = true;
		}
		/* Release가 true라는 뜻은, "이전 프레임에 Release를 했다는 의미"
		   즉, 이제는 Release도 아니다. (Release는 떼는 순간을 체크하기 위한 변수) */
		else if (iter->second->Release)
			iter->second->Release = false;
	}
}

// 등록된 키 정보를 비교하여, 해당 키 상태에 따라 등록된 함수들을 호출
void CInput::UpdateBindFunction()
{
	std::unordered_map<std::string, FBindKey*>::iterator	iter = mMapBindKey.begin();
	std::unordered_map<std::string, FBindKey*>::iterator	iterEnd = mMapBindKey.end();

	for (; iter != iterEnd; ++iter)
	{
		FBindKey* bindKey = iter->second;

		// KeyInfo에 등록된 키 && KeyInfo에 조합 키와 CInput 멤버 변수에 있는 키가 서로 대칭이 되는지 확인
		if (bindKey->Ctrl != mCtrl || bindKey->Alt != mAlt || bindKey->Shift != mShift)
			continue;

		if (bindKey->Key->Press)
			ExecuteBindFunctions(bindKey, EKeyType::Press);
		if (bindKey->Key->Hold)
			ExecuteBindFunctions(bindKey, EKeyType::Hold);
		if (bindKey->Key->Release)
			ExecuteBindFunctions(bindKey, EKeyType::Release);
	}
}

void CInput::ExecuteBindFunctions(FBindKey* BindKey, EKeyType::Type Type)
{
	std::vector<FBindFunction*>& functions = BindKey->vecFunction[Type];

	size_t size = functions.size();
	for (size_t i = 0; i < size; ++i)
	{
		functions[i]->func();
	}
}

FKeyInfo* CInput::FindKeyInfo(SDL_Scancode Key)
{
	std::unordered_map<SDL_Scancode, FKeyInfo*>::iterator	iter = mMapKeyInfo.find(Key);

	if (iter == mMapKeyInfo.end())
		return nullptr;

	return iter->second;
}

FBindKey* CInput::FindBindKey(const std::string& Key)
{
	std::unordered_map<std::string, FBindKey*>::iterator	iter = mMapBindKey.find(Key);

	if (iter == mMapBindKey.end())
		return nullptr;
	
	return iter->second;
}


bool CInput::CreateBindKey(const std::string& Key, SDL_Scancode Value)
{ 
	FBindKey* BindKey = FindBindKey(Key);

	if (BindKey)
		return false;

	BindKey = new FBindKey;

	// 등록 안된 키일 경우 새로 만들어준다.
	FKeyInfo* KeyInfo = FindKeyInfo(Value);
	if (!KeyInfo)
	{
		KeyInfo = new FKeyInfo;

		KeyInfo->Key = Value;

		mMapKeyInfo.insert(std::make_pair(Value, KeyInfo));
	}

	BindKey->Key = KeyInfo;
	BindKey->Name = Key;

	mMapBindKey.insert(std::make_pair(Key, BindKey));

	return true;
}
