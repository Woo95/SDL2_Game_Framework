#pragma once

#include "Widget.h"
#include "../Core/Utils/WidgetUtils.h"

class CTexture;

class CSlider : public CWidget
{
public:
	CSlider();
	virtual ~CSlider();

private:
	std::shared_ptr<CTexture> mTexture = nullptr;
	SDL_Rect  mFrames[ESlider::State::MAX] = {};
	SDL_Color mColors[ESlider::State::MAX] = {};
	
	bool  mIsDragging = false;
	float mThumbOffsetX = 0.0f;

	float mCurrentPercent = 0.5f;
	
	SDL_Rect mTrackRect = { 0, 0, 0, 10 };
	SDL_Rect mThumbRect = { 0, 0, 25, 0 };
	
private:
	virtual void Update(float DeltaTime) final;
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) final;
	virtual void Release() final;

	virtual void HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)   final;
	virtual void HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased) final;

public:
	float GetPercent() const { return mCurrentPercent; }

	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
	void SetColor(ESlider::State state, Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 alpha);

private:
	void ComputePercent(const FVector2D& mousePos);

	void UpdateTrackRect();
	void UpdateThumbRect();

	void RenderTrack(SDL_Renderer* Renderer, const FVector2D& topLeft);
	void RenderThumb(SDL_Renderer* Renderer, const FVector2D& topLeft);
};