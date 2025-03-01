#include "AssetManager.h"
#include "DataManager.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "UIManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mDataManager(nullptr),
	mTextureManager(nullptr),
	mAnimationManager(nullptr),
	mUIManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mDataManager);
	SAFE_DELETE(mAnimationManager);
	SAFE_DELETE(mTextureManager);
	SAFE_DELETE(mUIManager);
}

bool CAssetManager::Init()
{
	mDataManager      = new CDataManager;
	mTextureManager   = new CTextureManager;
	mAnimationManager = new CAnimationManager;
	mUIManager        = new CUIManager;

	if (!mTextureManager->Init())
		return false;

	mDataManager->LoadAllAnimationData();
	mDataManager->LoadAllUIData();

	return true;
}