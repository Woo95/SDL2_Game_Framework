#pragma once

#include "Image.h"

class CAnimatedImage : public CImage
{
public:
	CAnimatedImage();
	virtual ~CAnimatedImage();

private:
	int mCurrIdx = 0;

	bool mIsLoop = true;

	float mFrameInterval = 0;
	float mIntervalPerFrame = 0.3f;

private:
	virtual void Render(SDL_Renderer* Renderer);
	virtual void Update(float DeltaTime);

public:
	void SetIsLoop(bool isLoop)
	{
		mIsLoop = isLoop;
	}
	void SetIntervalPerFrame(float intervalPerFrame)
	{
		mIntervalPerFrame = intervalPerFrame;
	}
};