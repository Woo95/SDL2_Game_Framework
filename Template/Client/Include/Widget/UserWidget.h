#pragma once

#include "Widget.h"

// 사용자 정의 UI 위젯의 베이스 클래스
class CUserWidget abstract : public CWidget
{
public:
	CUserWidget();
	virtual ~CUserWidget();

private:
	bool mIsMovable = false;
	FVector2D mDragOffset = FVector2D::ZERO;

protected:
	virtual void Construct() = 0;
	virtual void Release()   = 0;

public:
	void SetInteractable(bool interactable)
	{
		mIsInteractable = interactable;
		mIsMovable &= mIsInteractable;
	}
	void SetMovable(bool movable)
	{
		mIsMovable = movable;
		mIsInteractable |= movable;
	}

protected:
	void HandleDragging(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased);
};