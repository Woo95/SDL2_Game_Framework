#pragma once

#include "../../Core/GameInfo.h"

class CTexture;

class CTextureManager
{
	friend class CAssetManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CTexture>> mTextures;

public:
	bool Init();

	bool LoadTexture(const std::string& key, const char* fileName);
	std::shared_ptr<CTexture> FindTexture(const std::string& key);
};