#include "ProgressBar.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"

CProgressBar::CProgressBar()
{
	mColors[EProgBar::State::BACK] = { 255, 255, 255, 255 };
	mColors[EProgBar::State::FILL] = { 255, 255, 255, 255 };
}

CProgressBar::~CProgressBar()
{
	mTexture = nullptr;
}

void CProgressBar::Render(SDL_Renderer* Renderer)
{
	RenderBack(Renderer);
	RenderFill(Renderer);

	CWidget::Render(Renderer);
}

void CProgressBar::RenderBack(SDL_Renderer* Renderer)
{
	const SDL_Color& color = mColors[EProgBar::State::BACK];
	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), color.a);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[EProgBar::State::BACK], &mRect);
}

void CProgressBar::RenderFill(SDL_Renderer* Renderer)
{
	// fillFrame 참조 및 원본 값 저장
	SDL_Rect& fillFrame = mFrames[EProgBar::State::FILL];
	const SDL_Rect originalFrame = fillFrame;
	const SDL_Rect originalRect  = mRect;

	// 좌-우 방향 프로그레스 바의 텍스쳐 및 출력 영역 처리
	if (mFillMethod == EProgBar::Method::LeftToRight)
	{
		fillFrame.w = (int)(fillFrame.w * mPercent);
		mRect.w = (int)(mRect.w * mPercent);
	}
	// 하-상 방향 프로그레스 바의 텍스쳐 및 출력 영역 처리
	else if (mFillMethod == EProgBar::Method::BottomToTop)
	{
		int newHeight = (int)(fillFrame.h * mPercent);
		fillFrame.y += fillFrame.h - newHeight;
		fillFrame.h = newHeight;

		newHeight = (int)(mRect.h * mPercent); 
		mRect.y += mRect.h - newHeight;
		mRect.h = newHeight;
	}

	const SDL_Color& color = mColors[EProgBar::State::FILL];
	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), color.a);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[EProgBar::State::FILL], &mRect);

	// 원본 텍스쳐 및 출력 영역 복원
	mFrames[EProgBar::State::FILL] = originalFrame;
	mRect = originalRect;
}

void CProgressBar::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
}

void CProgressBar::SetFrame(const std::string& key)
{
	const std::vector<SDL_Rect>* const framesPtr = CAssetManager::GetInst()->GetUIManager()->GetUIFrames(key);

	if (framesPtr)
	{
		for (size_t i = 0; i < EProgBar::State::MAX; i++)
			mFrames[i] = (*framesPtr)[i];
	}
}

void CProgressBar::SetColor(EProgBar::State state, Uint8 r, Uint8 g, Uint8 b)
{
	mColors[state].r = r;
	mColors[state].g = g;
	mColors[state].b = b;
}

void CProgressBar::SetAlpha(Uint8 alpha)
{
	for (size_t i = 0; i < EProgBar::State::MAX; i++)
		mColors[i].a = alpha;

	// 투명도를 고려한 블렌드로 설정
	SDL_SetTextureBlendMode(mTexture.get()->GetTexture(), SDL_BLENDMODE_BLEND);
}