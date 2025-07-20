#pragma once

#include "Image.h"

class CAnimatedImage : public CImage
{
public:
	CAnimatedImage();
	virtual ~CAnimatedImage();

private:
	int mCurrIdx = 0;

	bool mIsAnimating = true;
	bool mIsLoop = true;

	float mFrameInterval = 0.0f;
	float mIntervalPerFrame = 0.15f;

private:
	virtual void Update(float deltaTime) final;
	virtual void Render(SDL_Renderer* renderer, const FVector2D& topLeft = FVector2D::ZERO) final;
	virtual void Release() final;

public:
	void ResetAnimation()
	{
		mCurrIdx = 0;
		mFrameInterval = 0.0f;
	}
	void SetAnimating(bool isAnimating)
	{
		mIsAnimating = isAnimating;
	}
	void SetIsLoop(bool isLoop)
	{
		mIsLoop = isLoop;
	}
	void SetIntervalPerFrame(float intervalPerFrame)
	{
		mIntervalPerFrame = intervalPerFrame;
	}
};