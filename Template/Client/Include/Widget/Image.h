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

	// for the 9Slice
	FVector2D mSrcCorner = FVector2D::ZERO;
	float mCornerRatio = 0.0f;

private:
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) override;
	virtual void Release() override;

public:
	void Render9Slice(SDL_Renderer* Renderer, const SDL_Rect& renderRect);

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
};