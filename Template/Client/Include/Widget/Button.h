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
	SDL_Rect  mFrames[EButton::State::STATE_MAX] = {};
	SDL_Color mColor = { 255, 255, 255, 255 };

	// for the 9Slice
	FVector2D mSrcCorner = FVector2D::ZERO;
	float mCornerRatio = 0.0f;

	EButton::State mCurrentState = EButton::State::NORMAL;

	using EventCallback = std::function<void()>;
	std::vector<EventCallback> mEvent[EButton::InputEvent::INPUT_EVENT_MAX];

private:
	virtual void Render(SDL_Renderer* renderer, const FVector2D& topLeft = FVector2D::ZERO) final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased) final;
	virtual void HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased) final;

public:
	void Render9Slice(SDL_Renderer* renderer, const SDL_Rect& renderRect);

	void Set9SlicingCorner(const FVector2D& srcCorner)
	{
		mSrcCorner = srcCorner;
	}
	void SetCornerRatio(float ratio)
	{
		mCornerRatio = ratio;
	}

public:
	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 alpha);

	void AddCallback(EButton::InputEvent event, const EventCallback& callback)
	{
		mEvent[event].emplace_back(callback);
	}

private:
	void ExecuteCallback(EButton::InputEvent event)
	{
		if (mEvent[event].empty())
			return;

		for (const auto& callback : mEvent[event])
			callback();
	}
};