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

	SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[0], &renderRect);

	CWidget::Render(Renderer, topLeft);
}

void CImage::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CImage>(this);
}

void CImage::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
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