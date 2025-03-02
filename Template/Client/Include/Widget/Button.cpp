#include "Button.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"

CButton::CButton()
{
	mIsTriggerable = true;

	AddEventCallback(EWidgetInput::Event::UNHOVER, [this]() {mCurrentState = EButton::State::UNHOVER;});
	AddEventCallback(EWidgetInput::Event::HOVER,   [this]() {mCurrentState = EButton::State::HOVER;});
	AddEventCallback(EWidgetInput::Event::CLICK,   [this]() {mCurrentState = EButton::State::CLICK; });
	AddEventCallback(EWidgetInput::Event::HOLD,    [this]() {mCurrentState = EButton::State::CLICK; });
	AddEventCallback(EWidgetInput::Event::RELEASE, [this]() {mCurrentState = mMouseHovered ? EButton::State::HOVER : EButton::State::UNHOVER;});
}

CButton::~CButton()
{
	mTexture = nullptr;
}

void CButton::Render(SDL_Renderer* Renderer)
{
	CWidget::Render(Renderer);

	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mAlpha);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[mCurrentState], &mRect);
}

void CButton::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
}

void CButton::SetFrame(const std::string& key)
{
	const std::vector<SDL_Rect>* const button = CAssetManager::GetInst()->GetUIManager()->GetUIFrames(key);

	if (button)
	{
		for (size_t i = 0; i < EButton::State::MAX; i++)
		{
			mFrames[i] = (*button)[i];
		}
	}
}

void CButton::SetAlpha(Uint8 alpha)
{
	mAlpha = alpha;

	// 투명도를 고려한 블렌드로 설정
	SDL_SetTextureBlendMode(mTexture.get()->GetTexture(), SDL_BLENDMODE_BLEND);
}