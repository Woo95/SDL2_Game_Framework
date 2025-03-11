#include "FontManager.h"
#include "../../Resource/Font.h"

CFontManager::CFontManager()
{
}

CFontManager::~CFontManager()
{
	mFonts.clear();
}

bool CFontManager::Init()
{
	if (TTF_Init() != 0)
		return false;

	if (!LoadFont("Cormorant", "Cormorant.ttf", 32))
		return false;


	return true;
}

bool CFontManager::LoadFont(const std::string& key, const char* fileName, int fontSize)
{
	if (!FindFont(key))
	{
		std::shared_ptr<CFont> newFont = std::make_shared<CFont>();

		if (newFont->LoadFont(fileName, fontSize))
		{
			mFonts[key] = newFont;

			return true;
		}
	}
	return false;
}

bool CFontManager::UnloadFont(const std::string& key)
{
	if (FindFont(key))
	{
		mFonts.erase(key);

		return true;
	}
	return false;
}

std::shared_ptr<CFont> CFontManager::FindFont(const std::string& key)
{
	std::unordered_map<std::string, std::shared_ptr<CFont>>::iterator iter = mFonts.find(key);

	if (iter == mFonts.end())
		return nullptr;

	return iter->second;
}