#pragma once

#include "../Core/GameInfo.h"
#include "Widget.h"

namespace EButton
{
	enum State : unsigned char
	{
		UNHOVER,
		HOVER,
		CLICK,
		MAX
	};
}

class CTexture;

class CButton : public CWidget
{
public:
	CButton();
	virtual ~CButton();

private:
	std::shared_ptr<CTexture> mTexture = nullptr;
	SDL_Rect mFrames[EButton::State::MAX] = {};

	EButton::State mCurrentState = EButton::State::UNHOVER;

public:
	virtual void Render(SDL_Renderer* Renderer) override;

public:
	void SetTexture(const std::string& key);
	void SetButton(const std::string& key);
};