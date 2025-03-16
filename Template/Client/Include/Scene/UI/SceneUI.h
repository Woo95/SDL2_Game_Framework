#pragma once

#include "../../Core/GameInfo.h"
#include "../../Manager/MemoryPoolManager.h"

class CUserWidget;
class CWidget;

// container of the CUserWidgets
class CSceneUI
{
	friend class CScene;
	friend class CUserWidget;
	friend class CWidget;

public:
	CSceneUI();
	virtual ~CSceneUI();

private:
	std::vector<CUserWidget*> mUserWidgets;
	CUserWidget* mCurrHovered = nullptr;

	CWidget* mHeldWidget = nullptr;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	CUserWidget* FindUserWidget(const std::string& name = "");
	void BringUserWidgetToTop(CUserWidget* userWidget);

	CWidget* GetHeldWidget() const { return mHeldWidget; }
	void SetHeldWidget(CWidget* heldWidget) 
	{
		mHeldWidget = heldWidget; 
	}

	template <typename T, int initialCapacity = 10>
	T* CreateUserWidget(const std::string& name)
	{
		// 해당 타입의 메모리 풀이 없으면 새로 생성
		if (!CMemoryPoolManager::GetInst()->HasPool<T>())
		{
			CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
		}

		T* userWidget = CMemoryPoolManager::GetInst()->Allocate<T>();

		userWidget->SetName(name);
		userWidget->mSceneUI = this;

		mUserWidgets.emplace_back(userWidget);
		return userWidget;
	}

	template <typename T, int initialCapacity = 10>
	T* CreateWidget(const std::string& name)
	{
		// 해당 타입의 메모리 풀이 없으면 새로 생성
		if (!CMemoryPoolManager::GetInst()->HasPool<T>())
		{
			CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
		}

		T* widget = CMemoryPoolManager::GetInst()->Allocate<T>();

		widget->SetName(name);

		return widget;
	}

private:
	void UpdateInput();
};