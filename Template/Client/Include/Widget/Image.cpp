#include "Image.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Resource/Texture.h"

CImage::CImage()
{
}

CImage::~CImage()
{
	mTexture = nullptr;
}

void CImage::Render(SDL_Renderer* Renderer)
{
	CWidget::Render(Renderer);

	SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), mAlpha);

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrame, &mRect);
}

void CImage::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
}

void CImage::SetFrame(const std::string& key)
{
	const std::vector<SDL_Rect>* const image = CAssetManager::GetInst()->GetUIManager()->GetUIFrames(key);

	mFrame = (*image)[0];
}

void CImage::SetAlpha(Uint8 alpha)
{
	mAlpha = alpha;

	// 투명도를 고려한 블렌드로 설정
	SDL_SetTextureBlendMode(mTexture.get()->GetTexture(), SDL_BLENDMODE_BLEND);
}