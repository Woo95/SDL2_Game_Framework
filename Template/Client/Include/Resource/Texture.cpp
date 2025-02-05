#include "Texture.h"
#include "../Manager/Resource/PathManager.h"
#include "../Manager/GameManager.h"

CTexture::CTexture() : 
	mTexture(nullptr),
	mSize({0,0,0,0})
{
}

CTexture::~CTexture()
{
	SDL_DestroyTexture(mTexture);
}

bool CTexture::LoadTexture(const char* fileName)
{
	std::string imgPath = CPathManager::GetInst()->FindPath(TEXTURE_PATH);
	imgPath += "\\" + (std::string)fileName;

	// 이미지를 CPU 메모리로 읽어들여 SDL_Surface로 저장
	SDL_Surface* surface = IMG_Load(imgPath.c_str());

	if (surface)
	{
		// SDL_Surface를 GPU에서 사용할 수 있는 SDL_Texture로 변환
		SDL_Texture* texture = SDL_CreateTextureFromSurface(CGameManager::GetInst()->GetRenderer(), surface);

		SDL_FreeSurface(surface);

		if (texture)
		{
			mTexture = texture;
			SDL_QueryTexture(texture, nullptr, nullptr, &mSize.w, &mSize.h);

			return true;
		}
	}
	return false;
}