#include "AssetManager.h"
#include "DataManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "UIManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mDataManager(nullptr),
	mTextureManager(nullptr),
	mSpriteManager(nullptr),
	mAnimationManager(nullptr),
	mUIManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mDataManager);
	SAFE_DELETE(mSpriteManager);
	SAFE_DELETE(mAnimationManager);
	SAFE_DELETE(mTextureManager);
	SAFE_DELETE(mUIManager);
}

bool CAssetManager::Init()
{
	mDataManager      = new CDataManager;
	mTextureManager   = new CTextureManager;
	mSpriteManager    = new CSpriteManager;
	mAnimationManager = new CAnimationManager;
	mUIManager        = new CUIManager;

	if (!mTextureManager->Init())
		return false;

	mDataManager->LoadAllSpriteData();
	mDataManager->LoadAllAnimationData();
	mDataManager->LoadAllUIData();

	return true;
}