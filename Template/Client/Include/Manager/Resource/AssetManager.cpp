#include "AssetManager.h"
#include "TextureManager.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager()
{
}

CAssetManager::~CAssetManager()
{
}

bool CAssetManager::Init()
{
	return true;
}