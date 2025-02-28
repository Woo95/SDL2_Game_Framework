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

	bool mIsTriggerable = false;
	bool mMouseHovered  = false;

	std::unordered_map<EWidgetInput::Event, std::vector<std::function<void()>>> mEventCallbacks;

protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	void AddChild(CWidget* child);
	bool DeleteChild(CWidget* child);
	CWidget* FindWidget(size_t id);

	void AddEventCallback(EWidgetInput::Event event, const std::function<void()>& func)
	{
		mEventCallbacks[event].push_back(func);
	}

public:
	void Enable();
	void Disable();
	void Destroy();

private:
	CWidget* GetHoveredWidget(const FVector2D& mousePos);

	void HandleHovered(bool isPressed, bool isHeld, bool isReleased);
	void HandleUnhovered();

	void ExecuteCallback(EWidgetInput::Event event);
};