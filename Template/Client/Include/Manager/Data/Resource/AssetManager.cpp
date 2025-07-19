#include "AssetManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "UIManager.h"
#include "FontManager.h"
#include "SoundManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager(void* memoryBlock)
{
	mTextureManager   = PlacementNew<CTextureManager>(memoryBlock);
	mSpriteManager    = PlacementNew<CSpriteManager>(memoryBlock);
	mAnimationManager = PlacementNew<CAnimationManager>(memoryBlock);
	mUIManager        = PlacementNew<CUIManager>(memoryBlock);
	mFontManager      = PlacementNew<CFontManager>(memoryBlock);
	mSoundManager     = PlacementNew<CSoundManager>(memoryBlock);
}

CAssetManager::~CAssetManager()
{
	PlacementDelete<CTextureManager>(mTextureManager);
	PlacementDelete<CSpriteManager>(mSpriteManager);
	PlacementDelete<CAnimationManager>(mAnimationManager);
	PlacementDelete<CUIManager>(mUIManager);
	PlacementDelete<CFontManager>(mFontManager);
	PlacementDelete<CSoundManager>(mSoundManager);
}

CAssetManager* CAssetManager::GetInst()
{
	if (!mInst)
	{
		const size_t totalSize = sizeof(CAssetManager) + sizeof(CTextureManager) + sizeof(CSpriteManager) +
			sizeof(CAnimationManager) + sizeof(CUIManager) + sizeof(CFontManager) + sizeof(CSoundManager);

		void* memoryBlock = malloc(totalSize);
		mInst = new (memoryBlock) CAssetManager((char*)memoryBlock + sizeof(CAssetManager));
	}
	return mInst;
}

void CAssetManager::DestroyInst()
{
	if (mInst)
	{
		mInst->~CAssetManager();
		free(mInst);
	}
}