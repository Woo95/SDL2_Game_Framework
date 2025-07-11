#include "AssetManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "UIManager.h"
#include "FontManager.h"
#include "SoundManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mTextureManager(nullptr),
	mSpriteManager(nullptr),
	mAnimationManager(nullptr),
	mUIManager(nullptr),
	mFontManager(nullptr),
	mSoundManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mSpriteManager);
	SAFE_DELETE(mAnimationManager);
	SAFE_DELETE(mTextureManager);
	SAFE_DELETE(mUIManager);
	SAFE_DELETE(mFontManager);
	SAFE_DELETE(mSoundManager);
}

bool CAssetManager::Init()
{
	mTextureManager   = new CTextureManager;
	mSpriteManager    = new CSpriteManager;
	mAnimationManager = new CAnimationManager;
	mUIManager        = new CUIManager;
	mFontManager      = new CFontManager;
	mSoundManager     = new CSoundManager;

	if (!mTextureManager->Init() || !mFontManager->Init() || !mSoundManager->Init())
		return false;

	return true;
}