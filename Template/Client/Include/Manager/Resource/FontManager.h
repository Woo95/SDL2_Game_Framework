#pragma once

#include "../../Core/GameInfo.h"

class CFont;

class CFontManager
{
	friend class CAssetManager;

private:
	CFontManager();
	~CFontManager();

private:
	std::unordered_map<std::string, std::weak_ptr<CFont>> mFonts;

private:
	bool Init();

public:
	std::shared_ptr<CFont> LoadFont(const std::string& key, const char* fileName, int fontSize);
	std::shared_ptr<CFont> GetFont(const std::string& key);
};