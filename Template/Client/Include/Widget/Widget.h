#pragma once

#include "WidgetBase.h"

// 원초적인 UI 위젯의 기본 클래스
class CWidget abstract : public CWidgetBase
{
	friend class CSceneUI;
	friend class CWidgetComponent;

protected:
	CWidget();
	virtual ~CWidget();

protected:
	CSceneUI* mSceneUI = nullptr;

	CWidget* mParent = nullptr;
	std::vector<CWidget*> mChilds;

	bool mIsInteractable = false;
	bool mWidgetHovered  = false;
	bool mWidgetHeld     = false;

protected:
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer, const FVector2D& topLeft = FVector2D::ZERO);
	virtual void Release() = 0;

	// 마우스와 상호작용이 있는 위젯들에서 따로 구현
	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) {};
	virtual void HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased) {};

public:	
	CWidget* FindRootWidget();
	CWidget* FindWidget(size_t id);

	void AddChild(CWidget* child);
	bool DeleteChild(CWidget* child);

	CSceneUI* GetOwnerSceneUI() const { return mSceneUI; }

public:
	// 자신만 활성화/비활성화 (자식 영향 방지)
	void Enable() { SetEnable(true); }
	void Disable() { SetEnable(false); }
	// 자식까지 안전하게 제거
	void Destroy();
};