#pragma once

#include "../../Core/GameInfo.h"

class CTexture;
class CScene;

class CTextureManager
{
	friend class CAssetManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CTexture>> mTextures;

private:
	bool Init();

public:
	bool LoadTexture  (const std::string& key, const char* fileName, CScene* scene = nullptr);
	bool UnloadTexture(const std::string& key);
	std::shared_ptr<CTexture> FindTexture(const std::string& key);
};