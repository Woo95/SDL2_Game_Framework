#include "InputComponent.h"
#include "../../Manager/InputManager.h"

CInputComponent::CInputComponent()
{
	mTypeID = typeid(CInputComponent).hash_code();

	CMemoryPoolManager::GetInst()->CreatePool<FBinder>(20);
	CMemoryPoolManager::GetInst()->CreatePool<FBindFunction>(20);
}

CInputComponent::~CInputComponent()
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

void CInputComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	// 등록된 입력정보를 비교하여, 해당 입력상태에 따라 등록된 함수들을 호출 //
	std::unordered_map<std::string, FBinder*>::iterator iter = mBinders.begin();
	std::unordered_map<std::string, FBinder*>::iterator iterEnd = mBinders.end();

	for (; iter != iterEnd; iter++)
	{
		FBinder* binder = iter->second;
		if (binder->Keys.empty() && binder->Mouses.empty())
			continue;

		bool match = true;

		// KEYBOARD //
		for (const auto& binderKey : binder->Keys)
		{
			const SDL_Scancode& key = binderKey.first;
			const EKeyAction& action = binderKey.second;

			if (!CInputManager::GetInst()->GetKeyState(key, action))
			{
				match = false;
				break;
			}
		}

		if (!match)
			continue;

		// MOUSE //
		for (const auto& binderMouse : binder->Mouses)
		{
			const Uint8& mouse = binderMouse.first;
			const EKeyAction& action = binderMouse.second;

			if (!CInputManager::GetInst()->GetMouseButtonState(mouse, action))
			{
				match = false;
				break;
			}
		}

		if (match)
		{
			for (FBindFunction* bindFunc : binder->Functions)
				bindFunc->func();
		}
	}
}

void CInputComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CInputComponent>(this);
}