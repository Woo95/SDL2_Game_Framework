#include "AnimatedImage.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/TextureManager.h"
#include "../Manager/Data/Resource/UIManager.h"
#include "../Resource/Texture.h"

CAnimatedImage::CAnimatedImage()
{
}

CAnimatedImage::~CAnimatedImage()
{
}

void CAnimatedImage::Update(float deltaTime)
{
	CWidget::Update(deltaTime);

	if (!mIsAnimating)
		return;

	mFrameInterval += deltaTime;

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

void CAnimatedImage::Render(SDL_Renderer* renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), mColor.r, mColor.g, mColor.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mColor.a);

	SDL_RenderCopy(renderer, mTexture.get()->GetTexture(), &mFrames[mCurrIdx], &renderRect);

	CWidget::Render(renderer, topLeft);
}

void CAnimatedImage::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CAnimatedImage>(this);
}