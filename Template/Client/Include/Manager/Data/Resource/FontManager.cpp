#include "FontManager.h"
#include "../../../Resource/Font.h"

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

	return true;
}

std::shared_ptr<CFont> CFontManager::LoadFont(const std::string& key, const char* fileName, int fontSize)
{
	std::shared_ptr<CFont> font = GetFont(key);

	if (!font)
	{
		font = std::make_shared<CFont>();

		if (font->LoadFont(fileName, fontSize))
		{
			mFonts[key] = font;
		}
	}
	return font;
}

std::shared_ptr<CFont> CFontManager::GetFont(const std::string& key)
{
	std::unordered_map<std::string, std::weak_ptr<CFont>>::iterator iter = mFonts.find(key);

	if (iter == mFonts.end())
		return nullptr;

	return iter->second.lock();
}