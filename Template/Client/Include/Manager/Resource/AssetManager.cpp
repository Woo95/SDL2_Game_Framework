#include "AssetManager.h"
#include "TextureManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mTextureManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mTextureManager);
}

bool CAssetManager::Init()
{
	mTextureManager = new CTextureManager;

	if (!mTextureManager->Init())
		return false;

	return true;
}