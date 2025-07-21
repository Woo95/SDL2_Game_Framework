#include "TextureManager.h"
#include "../../../Resource/Texture.h"
#include "../../../Scene/Scene.h"

CTextureManager::CTextureManager()
{
	// PNG, JPG 포맷 지원을 위한 SDL2_image 초기화
	if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) != (IMG_INIT_PNG | IMG_INIT_JPG))
	{
		std::cerr << "CTextureManager IMG_Init failed: " << IMG_GetError() << "\n";
		throw std::runtime_error("Failed to initialize SDL_image");
	}
}

CTextureManager::~CTextureManager()
{
	mTextures.clear();

	IMG_Quit();
}

std::shared_ptr<CTexture> CTextureManager::LoadTexture(const std::string& key, const char* fileName)
{
	std::shared_ptr<CTexture> texture = GetTexture(key);

	if (!texture)
	{
		texture = std::make_shared<CTexture>();

		if (texture->LoadTexture(fileName))
		{
			mTextures[key] = texture;
		}
	}
	return texture;
}

std::shared_ptr<CTexture> CTextureManager::GetTexture(const std::string& key)
{
	std::unordered_map<std::string, std::weak_ptr<CTexture>>::iterator iter = mTextures.find(key);

	if (iter == mTextures.end())
		return nullptr;

	return iter->second.lock();
}