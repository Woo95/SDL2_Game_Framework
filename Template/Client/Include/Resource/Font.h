#pragma once

#include "../Core/GameInfo.h"
#include "../Core/External/SDL/SDL_ttf.h"

class CFont
{
	friend class CFontManager;

public:
	CFont();
	~CFont();

private:
	TTF_Font* mFont = nullptr;

public:
	TTF_Font* GetFont() const { return mFont; }

private:
	bool LoadFont(const char* fileName, int fontSize);
};