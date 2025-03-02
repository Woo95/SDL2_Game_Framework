#pragma once

#include "WidgetBase.h"
#include "../Core/GameInfo.h"

class CWidget;

class CUserWidget : public CWidgetBase
{
	friend class CSceneUI;
	friend class CWidget;

private:
	CUserWidget();
	virtual ~CUserWidget();

private:
	CSceneUI* mSceneUI = nullptr;

	bool mIsMovable = false;
	FVector2D mDragOffset = FVector2D::ZERO;

	std::vector<CWidget*> mWidgets;
	CWidget* mCurrHovered = nullptr;

protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	void SetMovable(bool movable)
	{
		mIsMovable = movable;
	}

	CWidget* FindWidget(size_t id);

	template <typename T>
	void AddWidget(T* widget)
	{
		widget->mUserWidget = this;

		mWidgets.emplace_back(widget);
		widget->SetZOrder(0);

		mTransform->AddChild(widget->mTransform);
	}

public:
	void Enable();
	void Disable();
	void Destroy();

private:
	void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased);
	void HandleUnhovered();
	void HandleDragging(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased);

	void BringToTop();
};