#include "TextBlock.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/FontManager.h"
#include "../Resource/Font.h"

CTextBlock::CTextBlock()
{
}

CTextBlock::~CTextBlock()
{
	if (mShadowTexture)
	{
		SDL_DestroyTexture(mShadowTexture);
		mShadowTexture = nullptr;
	}
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
	mFont = nullptr;
}

void CTextBlock::Render(SDL_Renderer* renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	if (mIsTextFitNeeded)
		FitTextWidthToRect(renderRect);

	ApplyAlignment(renderRect);

	if (mHasShadow)
	{
		UpdateTextTexture(renderer, mUpdateShadowTexture, mShadowTexture, mShadowColor);

		renderRect.x += (int)mShadowOffset.x;
		renderRect.y += (int)mShadowOffset.y;

		SDL_RenderCopy(renderer, mShadowTexture, nullptr, &renderRect);

		renderRect.x -= (int)mShadowOffset.x;
		renderRect.y -= (int)mShadowOffset.y;
	}
	UpdateTextTexture(renderer, mUpdateTexture, mTexture, mColor);
	SDL_RenderCopy(renderer, mTexture, nullptr, &renderRect);

	CWidget::Render(renderer, topLeft);
}

void CTextBlock::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CTextBlock>(this);
}

void CTextBlock::FitTextWidthToRect(const SDL_Rect& renderRect)
{
	if (mText.empty())
		return;

	mTextWidth = mCharWidth * mText.length();

	if (renderRect.w < mTextWidth)
		mTextWidth = (float)renderRect.w;

	mIsTextFitNeeded = false;
}

void CTextBlock::ApplyAlignment(SDL_Rect& renderRect)
{
	if (mAlignment == ETextBlock::Alignment::FILL)
		return;

	int offsetX = 0;
	switch (mAlignment)
	{
	case ETextBlock::Alignment::LEFT:
		break;
	case ETextBlock::Alignment::CENTER:
		offsetX = (int)((renderRect.w - mTextWidth) * 0.5f);
		break;
	case ETextBlock::Alignment::RIGHT:
		offsetX = renderRect.w - (int)mTextWidth;
		break;
	}

	renderRect.x += offsetX;
	renderRect.w = (int)mTextWidth;
}

void CTextBlock::UpdateTextTexture(SDL_Renderer* renderer, bool& updateTexture, SDL_Texture*& texture, SDL_Color color)
{
	if (updateTexture)
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
		// 텍스트를 CPU 메모리에 SDL_Surface로 생성
		SDL_Surface* surface = TTF_RenderText_Blended(mFont.get()->GetFont(), mText.c_str(), color);

		// SDL_Surface를 GPU에서 사용할 수 있는 SDL_Texture로 변환
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);

		updateTexture = false;
	}
}

void CTextBlock::SetFont(const std::string& key)
{
	mFont = CAssetManager::GetInst()->GetFontManager()->GetFont(key);
}

void CTextBlock::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;

	mUpdateTexture = true;
}

void CTextBlock::SetShadowColor(Uint8 r, Uint8 g, Uint8 b)
{
	mShadowColor.r = r;
	mShadowColor.g = g;
	mShadowColor.b = b;

	mUpdateShadowTexture = true;
}

void CTextBlock::SetShadowOffset(float x, float y)
{
	mShadowOffset.x = x;
	mShadowOffset.y = y;
}

void CTextBlock::SetText(const std::string& text)
{
	if (mText != text)
	{
		mText = text;
		mIsTextFitNeeded = true;
		mUpdateTexture   = true;
	}
}

void CTextBlock::AddText(const std::string& text)
{
	if (!text.empty())
	{
		mText += text;
		mIsTextFitNeeded = true;
		mUpdateTexture   = true;
	}
}

void CTextBlock::ClearText()
{
	if (!mText.empty())
	{
		mText.clear();
		mIsTextFitNeeded = true;
		mUpdateTexture   = true;
	}
}

void CTextBlock::SetCharWidth(float charWidth)
{
	mCharWidth = charWidth;
	mIsTextFitNeeded = true;
}