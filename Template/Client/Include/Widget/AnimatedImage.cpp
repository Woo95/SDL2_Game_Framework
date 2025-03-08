#include "AnimatedImage.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"
#include "../Manager/MemoryPoolManager.h"

CAnimatedImage::CAnimatedImage()
{
}

CAnimatedImage::~CAnimatedImage()
{
}

void CAnimatedImage::Update(float DeltaTime)
{
	CWidget::Update(DeltaTime);

	mFrameInterval += DeltaTime;

	if (mFrameInterval >= mIntervalPerFrame)
	{
		if (mIsLoop)
			mCurrIdx = (mCurrIdx + 1) % mFrames.size();
		else if (mCurrIdx < mFrames.size() - 1)
		{
			mCurrIdx++;
		}
		mFrameInterval = 0.0f;
	}
}

void CAnimatedImage::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), mColor.r, mColor.g, mColor.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mColor.a);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[mCurrIdx], &renderRect);

	CWidget::Render(Renderer, topLeft);
}

void CAnimatedImage::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CAnimatedImage>(this);
}