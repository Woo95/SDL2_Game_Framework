#include "Button.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"
#include "../Manager/MemoryPoolManager.h"

CButton::CButton()
{
	mIsTriggerable = true;

	AddEventCallback(EWidgetInput::Event::UNHOVER, [this]() {mCurrentState = EButton::State::UNHOVER;});
	AddEventCallback(EWidgetInput::Event::HOVER,   [this]() {mCurrentState = EButton::State::HOVER;});
	AddEventCallback(EWidgetInput::Event::CLICK,   [this]() {mCurrentState = EButton::State::CLICK;});
	AddEventCallback(EWidgetInput::Event::HOLD,    [this]() {mCurrentState = EButton::State::CLICK;});
	AddEventCallback(EWidgetInput::Event::RELEASE, [this]() {mCurrentState = mMouseHovered ? EButton::State::HOVER : EButton::State::UNHOVER;});
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

void CButton::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
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