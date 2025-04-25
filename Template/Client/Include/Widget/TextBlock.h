#pragma once

#include "Widget.h"

class CFont;

class CTextBlock : public CWidget
{
public:
	CTextBlock();
	virtual ~CTextBlock();

private:
	std::shared_ptr<CFont> mFont = nullptr;
	std::string mText = "";

	// text fit
	float mCharWidth = 0.0f;
	float mTextWidth = 0.0f;
	bool mIsTextFitNeeded = false;

	// text
	SDL_Texture* mTexture = nullptr;
	bool mUpdateTexture = true;
	SDL_Color mColor = { 255, 255, 255, 255 };

	// shadow text
	bool mHasShadow = false;
	SDL_Texture* mShadowTexture = nullptr;
	bool mUpdateShadowTexture = true;
	SDL_Color mShadowColor = { 0, 0, 0, 255 };
	FVector2D mShadowOffset = { 2.f, 2.f };

	ETextBlock::Alignment mAlignment = ETextBlock::Alignment::FILL;

private:
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) final;
	virtual void Release() final;

	void FitTextWidthToRect(const SDL_Rect& renderRect);
	void ApplyAlignment(SDL_Rect& renderRect);
	void UpdateTextTexture(SDL_Renderer* Renderer, bool& updateTexture, SDL_Texture*& texture, SDL_Color color);

public:
	const std::string& GetText() const { return mText; }

	void SetFont(const std::string& key);

	void SetColor(Uint8 r, Uint8 g, Uint8 b);

	void EnableShadow(bool enable) { mHasShadow = enable; }
	void SetShadowColor(Uint8 r, Uint8 g, Uint8 b);
	void SetShadowOffset(float x, float y);

	void SetText(const std::string& text);
	void AddText(const std::string& text);
	void ClearText();

	// Ignored if alignment is FILL
	void SetCharWidth(float charWidth);
	// Ignored if charWidth has not been set
	void SetAlignment(ETextBlock::Alignment alignment) { mAlignment = alignment; }
};