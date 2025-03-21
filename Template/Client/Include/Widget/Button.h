#pragma once

#include "Widget.h"
#include "../Core/Utils/WidgetUtils.h"

class CTexture;

class CButton : public CWidget
{
public:
	CButton();
	virtual ~CButton();

private:
	std::shared_ptr<CTexture> mTexture = nullptr;
	SDL_Rect  mFrames[EButton::State::MAX] = {};
	SDL_Color mColor = { 255, 255, 255, 255 };

	EButton::State mCurrentState = EButton::State::NORMAL;

private:
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) final;
	virtual void Release() final;
	
	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;
	virtual void HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased) final;

public:
	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 alpha);
};