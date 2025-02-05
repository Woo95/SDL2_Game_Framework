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

	LoadTextures();

	return true;
}

void CAssetManager::LoadTextures()
{
	mTextureManager->LoadTexture("Antonio", "Antonio.png");
	mTextureManager->LoadTexture("Imelda", "Imelda.png");
	mTextureManager->LoadTexture("Pasqualina", "Pasqualina.png");
	mTextureManager->LoadTexture("Bullet", "Bullet.png");
	mTextureManager->LoadTexture("Stage1", "Mad_Forest_stage_1.png");
	mTextureManager->LoadTexture("Stage2", "Inlaid_Library_stage_2.png");
}