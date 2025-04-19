#pragma once

#include "UserWidget.h"

class CSampleUserWidget : public CUserWidget
{
public:
	CSampleUserWidget();
	virtual ~CSampleUserWidget();

protected:
	virtual void Construct() override;
	virtual void Release() override;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) override;
	virtual void HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased) override;
};