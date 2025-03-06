#include "AssetManager.h"
#include "DataManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "UIManager.h"
#include "FontManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mDataManager(nullptr),
	mTextureManager(nullptr),
	mSpriteManager(nullptr),
	mAnimationManager(nullptr),
	mUIManager(nullptr),
	mFontManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mDataManager);
	SAFE_DELETE(mSpriteManager);
	SAFE_DELETE(mAnimationManager);
	SAFE_DELETE(mTextureManager);
	SAFE_DELETE(mUIManager);
	SAFE_DELETE(mFontManager);
}

bool CAssetManager::Init()
{
	mDataManager      = new CDataManager;
	mTextureManager   = new CTextureManager;
	mSpriteManager    = new CSpriteManager;
	mAnimationManager = new CAnimationManager;
	mUIManager        = new CUIManager;
	mFontManager      = new CFontManager;

	if (!mDataManager->Init())
		return false;

	if (!mTextureManager->Init())
		return false;

	if (!mFontManager->Init())
		return false;

	return true;
}