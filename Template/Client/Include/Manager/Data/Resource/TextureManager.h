#pragma once

#include "../../../Core/GameInfo.h"

class CTexture;
class CScene;

class CTextureManager
{
	friend class CAssetManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	std::unordered_map<std::string, std::weak_ptr<CTexture>> mTextures;

public:
	std::shared_ptr<CTexture> LoadTexture(const std::string& key, const char* fileName);
	std::shared_ptr<CTexture> GetTexture(const std::string& key);
};