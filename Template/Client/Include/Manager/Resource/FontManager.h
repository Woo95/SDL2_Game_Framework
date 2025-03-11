#pragma once

#include "../../Core/GameInfo.h"

class CFont;

class CFontManager
{
	friend class CAssetManager;
	friend class CDataManager;

private:
	CFontManager();
	~CFontManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CFont>> mFonts;

private:
	bool Init();

public:
	bool LoadFont(const std::string& key, const char* fileName, int fontSize);
	bool UnloadFont(const std::string& key);
	std::shared_ptr<CFont> FindFont(const std::string& key);
};