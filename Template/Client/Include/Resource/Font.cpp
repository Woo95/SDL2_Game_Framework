#include "Font.h"
#include "../Manager/Resource/PathManager.h"

CFont::CFont()
{
}

CFont::~CFont()
{
	if (mFont)
	{
		TTF_CloseFont(mFont);
		mFont = nullptr;
	}
}

bool CFont::LoadFont(const char* fileName, int fontSize)
{
	std::string fontPath = CPathManager::GetInst()->FindPath(FONT_PATH);
	fontPath += (std::string)fileName;

	mFont = TTF_OpenFont(fontPath.c_str(), fontSize);

	return mFont != nullptr;
}