#pragma once

#include "../Core/GameInfo.h"
#include "../Core/External/SDL/SDL_image.h"

class CTexture
{
	friend class CTextureManager;

public:
	CTexture();
	~CTexture();

private:
	SDL_Texture* mTexture;

public:
	SDL_Texture* GetTexture() const { return mTexture; }

private:
	bool LoadTexture(const char* fileName, const std::string& texturePathKey = TEXTURE_PATH);
};