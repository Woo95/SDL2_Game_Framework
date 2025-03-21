#include "Button.h"
#include "UserWidget.h"
#include "../Scene/UI/SceneUI.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Resource/Texture.h"
#include "../Manager/MemoryPoolManager.h"

CButton::CButton()
{
	mIsInteractable = true;
}

CButton::~CButton()
{
	mTexture = nullptr;
}

void CButton::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetTextureColorMod(mTexture.get()->GetTexture(), mColor.r, mColor.g, mColor.b);
	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mColor.a);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[mCurrentState], &renderRect);

	CWidget::Render(Renderer, topLeft);
}

void CButton::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CButton>(this);
}

void CButton::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
	// 만약 잡혀 있는 위젯이 존재하고, 현재 위젯이 아니면 처리하지 않음
	CWidget* currHeld = mUserWidget->GetSceneUI()->GetHeldWidget();
	if (currHeld && currHeld != this)
		return;

	// 위젯 최초로 호버할 때 처리
	if (!mMouseHovered)
	{
		mMouseHovered = true;

		if (currHeld == this)
		{
			mCurrentState = EButton::State::HOLD;
			ExecuteCallback(EWidgetInput::Event::HOLD);
		}
		else
		{
			mCurrentState = EButton::State::HOVER;
			ExecuteCallback(EWidgetInput::Event::HOVER);
		}
	}
	// 위젯 호버 중일 때 처리
	else
	{
		if (isPressed && !currHeld)
		{
			mUserWidget->GetSceneUI()->SetHeldWidget(this);
			mUserWidget->GetSceneUI()->BringUserWidgetToTop(mUserWidget);

			mCurrentState = EButton::State::HOLD;
			ExecuteCallback(EWidgetInput::Event::CLICK);
		}
		else if (isHeld && currHeld == this)
		{
			mCurrentState = EButton::State::HOLD;
			ExecuteCallback(EWidgetInput::Event::HOLD);
		}
		else if (isReleased && currHeld == this)
		{
			mUserWidget->GetSceneUI()->SetHeldWidget(nullptr);

			mCurrentState = EButton::State::HOVER;
			ExecuteCallback(EWidgetInput::Event::RELEASE);
		}
	}
}

void CButton::HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased)
{
	// 이전 프레임에서 위젯이 호버 상태였다면, 1회 실행
	if (mMouseHovered)
	{
		mMouseHovered = false;

		mCurrentState = EButton::State::NORMAL;
		ExecuteCallback(EWidgetInput::Event::UNHOVER);
	}
	else
	{
		// 마우스 좌클릭을 위젯 밖에서 홀드 하다가 떼었을 때 실행
		if (isReleased)
		{
			mUserWidget->GetSceneUI()->SetHeldWidget(nullptr);
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

	if (framesPtr)
	{
		for (size_t i = 0; i < EButton::State::MAX; i++)
		{
			mFrames[i] = (*framesPtr)[i];
		}
	}
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