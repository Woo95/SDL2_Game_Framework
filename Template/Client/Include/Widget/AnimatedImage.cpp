#include "AnimatedImage.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"

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

void CAnimatedImage::Render(SDL_Renderer* Renderer)
{
	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), mColor.r, mColor.g, mColor.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mColor.a);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[mCurrIdx], &mRect);

	CWidget::Render(Renderer);
}