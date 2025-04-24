#include "Image.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"
#include "../Manager/MemoryPoolManager.h"

CImage::CImage()
{
}

CImage::~CImage()
{
	mTexture = nullptr;
}

void CImage::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), mColor.r, mColor.g, mColor.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mColor.a);

	if ((mSrcCorner.x + mSrcCorner.y) > 0.0f)
		Render9Slice(Renderer, renderRect);
	else
		SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[0], &renderRect);

	CWidget::Render(Renderer, topLeft);
}

void CImage::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CImage>(this);
}

void CImage::Render9Slice(SDL_Renderer* Renderer, const SDL_Rect& renderRect)
{
	const SDL_Rect& srcRect = mFrames[0];

	int srcCornerW = (int)mSrcCorner.x;
	int srcCornerH = (int)mSrcCorner.y;

	int dstCornerW = (int)(srcCornerW * mCornerRatio);
	int dstCornerH = (int)(srcCornerH * mCornerRatio);

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			SDL_Rect srcPart =
			{
				srcRect.x + (col == 0 ? 0 : (col == 1 ? srcCornerW : srcRect.w - srcCornerW)),
				srcRect.y + (row == 0 ? 0 : (row == 1 ? srcCornerH : srcRect.h - srcCornerH)),
				(col == 1 ? srcRect.w - srcCornerW * 2 : srcCornerW),
				(row == 1 ? srcRect.h - srcCornerH * 2 : srcCornerH)
			};

			SDL_Rect dstPart =
			{
				renderRect.x + (col == 0 ? 0 : (col == 1 ? dstCornerW : renderRect.w - dstCornerW)),
				renderRect.y + (row == 0 ? 0 : (row == 1 ? dstCornerH : renderRect.h - dstCornerH)),
				(col == 1 ? renderRect.w - dstCornerW * 2 : dstCornerW),
				(row == 1 ? renderRect.h - dstCornerH * 2 : dstCornerH)
			};

			SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &srcPart, &dstPart);
		}
	}
}

void CImage::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->GetTexture(key);
}

void CImage::SetFrame(const std::string& key)
{
	const std::vector<SDL_Rect>* const framePtr = CAssetManager::GetInst()->GetUIManager()->GetUIFrames(key);

	mFrames = *framePtr;
}

void CImage::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
}

void CImage::SetAlpha(Uint8 alpha)
{
	mColor.a = alpha;

	// 투명도를 고려한 블렌드로 설정
	SDL_SetTextureBlendMode(mTexture.get()->GetTexture(), SDL_BLENDMODE_BLEND);
}