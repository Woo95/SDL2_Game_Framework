#pragma once

#include "../../Core/GameInfo.h"

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

	template <typename T>
	T* CreateUserWidget(const std::string& name)
	{
		T* userWidget = new T;

		userWidget->SetName(name);
		userWidget->mSceneUI = this;

		if (!userWidget->Init())
		{
			SAFE_DELETE(userWidget);
			return nullptr;
		}

		mUserWidgets.emplace_back(userWidget);
		return userWidget;
	}

	template <typename T>
	T* CreateWidget(const std::string& name)
	{
		T* widget = new T;

		widget->SetName(name);

		if (!widget->Init())
		{
			SAFE_DELETE(widget);
			return nullptr;
		}

		return widget;
	}

private:
	void UpdateInput();

	CWidget* GetHeldWidget() const { return mHeldWidget; }
	void SetHeldWidget(CWidget* heldWidget) { mHeldWidget = heldWidget; }

	void BringUserWidgetToTop(CUserWidget* userWidget);
};