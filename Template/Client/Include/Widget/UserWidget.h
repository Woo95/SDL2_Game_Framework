#pragma once

#include "WidgetBase.h"
#include "../Core/GameInfo.h"

class CWidget;

class CUserWidget : public CWidgetBase
{
	friend class CSceneUI;
	friend class CWidget;

public:
	CUserWidget();
	virtual ~CUserWidget();

private:
	CSceneUI* mSceneUI = nullptr;

	bool mIsMovable = false;
	FVector2D mDragOffset = FVector2D::ZERO;

	std::vector<CWidget*> mWidgets;
	CWidget* mCurrHovered = nullptr;

protected:
	virtual void Update(float DeltaTime)     override;
	virtual void LateUpdate(float DeltaTime) override;
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) override;
	virtual void Release() override;

public:
	CSceneUI* GetSceneUI() const { return mSceneUI; }

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

		mTransform->AddChild(widget->mTransform);
	}

public:
	void Enable();
	void Disable();
	void Destroy();

private:
	CWidget* FindHoveredWidget(const FVector2D& mousePos);

	void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased);
	void HandleUnhovered(const FVector2D& mousePos);
	void HandleDragging(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased);
};