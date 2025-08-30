#include "Button.h"
#include "../Scene/Extension/SceneUI.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/TextureManager.h"
#include "../Manager/Data/Resource/UIManager.h"
#include "../Resource/Texture.h"

CButton::CButton()
{
	mIsInteractable = true;
}

CButton::~CButton()
{
	mTexture = nullptr;
}

void CButton::Render(SDL_Renderer* renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), mColor.r, mColor.g, mColor.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mColor.a);

	if ((mSrcCorner.x + mSrcCorner.y) > 0.0f)
		Render9Slice(renderer, renderRect);
	else
		SDL_RenderCopy(renderer, mTexture.get()->GetTexture(), &mFrames[mCurrentState], &renderRect);

	CWidget::Render(renderer, topLeft);
}

void CButton::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CButton>(this);
}

void CButton::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
	// 이전 프레임에서 위젯이 "언호버" 상태였다면, 단 1회 실행
	if (!mWidgetHovered)
	{
		mWidgetHovered = true;

		mCurrentState = mWidgetHeld ? EButton::State::PRESSED : EButton::State::HOVER;
		return;
	}

	// 위젯 호버 상태에서 "마우스 입력" 처리 //

	if (isPressed && !mWidgetHeld)
	{
		mWidgetHeld = true;

		mSceneUI->SetHeldWidget(this);
		mSceneUI->BringWidgetToTop(FindRootWidget());

		mCurrentState = EButton::State::PRESSED;
		ExecuteCallback(EButton::InputEvent::CLICK);
	}
	else if (isHeld && mWidgetHeld)
	{
		ExecuteCallback(EButton::InputEvent::HOLD);
	}
	else if (isReleased && mWidgetHeld)
	{
		mWidgetHeld = false;

		mSceneUI->SetHeldWidget(nullptr);

		mCurrentState = EButton::State::HOVER;
		ExecuteCallback(EButton::InputEvent::RELEASE);
	}
}

void CButton::HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased)
{
	// 이전 프레임에서 위젯이 "호버" 상태였다면, 단 1회 실행
	if (mWidgetHovered)
	{
		mWidgetHovered = false;

		mCurrentState = EButton::State::NORMAL;
		return;
	}

	// 마우스 좌클릭을 위젯 안에서 홀드 하다가 밖일 때 실행
	if (isHeld && mWidgetHeld)
	{
		ExecuteCallback(EButton::InputEvent::HOLD);
	}
	// 마우스 좌클릭을 위젯 밖에서 홀드 하다가 떼었을 때 실행
	else if (isReleased)
	{
		mWidgetHeld = false;

		mSceneUI->SetHeldWidget(nullptr);
	}
}

void CButton::Render9Slice(SDL_Renderer* renderer, const SDL_Rect& renderRect)
{
	const SDL_Rect& srcRect = mFrames[mCurrentState];

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

			SDL_RenderCopy(renderer, mTexture.get()->GetTexture(), &srcPart, &dstPart);
		}
	}
}
void CButton::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->GetTexture(key);
}

void CButton::SetFrame(const std::string& key)
{
	const std::vector<SDL_Rect>* const framesPtr = CAssetManager::GetInst()->GetUIManager()->GetUIFrames(key);

	for (size_t i = 0; i < EButton::State::STATE_MAX; i++)
		mFrames[i] = (*framesPtr)[i];
}

void CButton::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
}

void CButton::SetAlpha(Uint8 alpha)
{
	mColor.a = alpha;

	// 투명도를 고려한 블렌드로 설정
	SDL_SetTextureBlendMode(mTexture.get()->GetTexture(), SDL_BLENDMODE_BLEND);
}