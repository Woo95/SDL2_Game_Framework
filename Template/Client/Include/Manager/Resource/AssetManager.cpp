#include "AssetManager.h"
#include "DataManager.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "../../Resource/Animation.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mDataManager(nullptr),
	mTextureManager(nullptr),
	mAnimationManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mDataManager);
	SAFE_DELETE(mAnimationManager);
	SAFE_DELETE(mTextureManager);
}

bool CAssetManager::Init()
{
	mDataManager      = new CDataManager;
	mTextureManager   = new CTextureManager;
	mAnimationManager = new CAnimationManager;

	if (!mTextureManager->Init())
		return false;

	mDataManager->LoadAllAnimationData();

	return true;
}