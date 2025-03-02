#pragma once

#include "Widget.h"

class CTexture;

class CImage : public CWidget
{
public:
	CImage();
	virtual ~CImage();

protected:
	std::shared_ptr<CTexture> mTexture = nullptr;
	std::vector<SDL_Rect> mFrames;
	Uint8 mAlpha = 255;

public:
	virtual void Render(SDL_Renderer* Renderer);

public:
	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
	void SetAlpha(Uint8 alpha);
};