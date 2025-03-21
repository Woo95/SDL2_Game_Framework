#pragma once

#include "WidgetBase.h"
#include "../Core/Utils/WidgetUtils.h"
#include "../Core/GameInfo.h"

// UI 위젯의 기본 클래스
class CWidget abstract : public CWidgetBase
{
	friend class CSceneUI;
	friend class CUserWidget;

protected:
	CWidget();
	virtual ~CWidget();

protected:
	CUserWidget* mUserWidget = nullptr;

	CWidget* mParent = nullptr;
	std::vector<CWidget*> mChilds;

	bool mIsInteractable = false;
	bool mMouseHovered   = false;

	std::unordered_map<EWidgetInput::Event, std::vector<std::function<void()>>> mEventCallbacks;

protected:
	virtual void Update(float DeltaTime)     override;
	virtual void LateUpdate(float DeltaTime) override;
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) override;
	virtual void Release() = 0;

	// 마우스와 상호작용이 있는 위젯들에서 따로 구현
	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) {};
	virtual void HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased) {};

public:
	CWidget* FindWidget(size_t id);

	void AddChild(CWidget* child);
	bool DeleteChild(CWidget* child);

	void AddEventCallback(EWidgetInput::Event event, const std::function<void()>& func)
	{
		mEventCallbacks[event].push_back(func);
	}

public:
	void Enable();
	void Disable();
	void Destroy();

protected:
	CWidget* FindHoveredWidget(const FVector2D& mousePos);

	void ExecuteCallback(EWidgetInput::Event event);
};