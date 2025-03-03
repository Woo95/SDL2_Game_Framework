#pragma once

#include "Widget.h"
#include "../Core/Utils/WidgetUtils.h"

class CTexture;

class CProgressBar : public CWidget
{
public:
	CProgressBar();
	virtual ~CProgressBar();

private:
	std::shared_ptr<CTexture> mTexture = nullptr;
	SDL_Rect  mFrames[EProgBar::State::MAX] = {};
	SDL_Color mColors[EProgBar::State::MAX] = {};

	float mPercent = 1.0f;
	EProgBar::Method mFillMethod = EProgBar::Method::LeftToRight;

private:
	virtual void Render(SDL_Renderer* Renderer);

	void RenderBack(SDL_Renderer* Renderer);
	void RenderFill(SDL_Renderer* Renderer);

public:
	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
	void SetColor(EProgBar::State state, Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 alpha);

	void SetPercent(float percent) 
	{
		if (percent <= 0.0f) 
			mPercent = 0.0f;
		else if (percent >= 1.0f) 
			mPercent = 1.0f;
		else 
			mPercent = percent;
	}
	void SetFillMethod(EProgBar::Method method)
	{
		mFillMethod = method;
	}
};