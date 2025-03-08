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
	SDL_Color mColor = { 255, 255, 255, 255 };

private:
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) override;
	virtual void Release() override;

public:
	void SetTexture(const std::string& key);
	void SetFrame(const std::string& key);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void SetAlpha(Uint8 alpha);
};