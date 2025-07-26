#pragma once

#include "../../Core/GameInfo.h"
#include "../../Core/Vector2D.h"

class CWidget;

// container of the CWidgets
class CSceneUI
{
public:
	CSceneUI();
	virtual ~CSceneUI();

private:
	std::vector<CWidget*> mWidgets;

	CWidget* mCurrHovered = nullptr;
	CWidget* mHeldWidget  = nullptr;

public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

public:
	CWidget* FindWidget(size_t id);

	void BringWidgetToTop(CWidget* widget);

	CWidget* GetHeldWidget() const { return mHeldWidget; }
	void SetHeldWidget(CWidget* heldWidget)
	{
		mHeldWidget = heldWidget;
	}

protected:
	void AddWidget(CWidget* widget)
	{
		mWidgets.emplace_back(widget);

		SetSceneUI(widget);
	}

private:
	void SetSceneUI(CWidget* widget);

	CWidget* FindHoveredWidget(const FVector2D& mousePos);
	CWidget* FindHoveredInTree(CWidget* widget, const FVector2D& mousePos);

	void UpdateInput();
};