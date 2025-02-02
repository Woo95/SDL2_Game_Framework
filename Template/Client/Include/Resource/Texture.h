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

    SDL_Rect mSize;

public:
    SDL_Texture* GetTexture()  const { return mTexture; }
    const SDL_Rect& GetTextureFrame() const { return mSize; }

private:
	bool LoadTexture(const char* fileName, const std::string& texturePathKey = TEXTURE_PATH);
};