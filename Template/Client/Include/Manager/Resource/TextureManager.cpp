#include "TextureManager.h"
#include "../../Resource/Texture.h"

CTextureManager::CTextureManager()
{
	// PNG, JPG 포맷 지원을 위한 SDL2_image 초기화
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

CTextureManager::~CTextureManager()
{
	mTextures.clear();

	IMG_Quit();
}

bool CTextureManager::Init()
{
	LoadTexture("Antonio", "Antonio.png", TEXTURE_PATH);

	return true;
}

bool CTextureManager::LoadTexture(const std::string& key, const char* fileName, const std::string& basePathKey)
{
	std::shared_ptr<CTexture> texture = FindTexture(key);

	if (!texture)
	{
		std::shared_ptr<CTexture> newTexture = std::make_shared<CTexture>();

		if (newTexture->LoadTexture(fileName, basePathKey))
		{
			mTextures[key] = newTexture;

			return true;
		}
	}
	return false;
}

std::shared_ptr<CTexture> CTextureManager::FindTexture(const std::string& key)
{
	std::unordered_map<std::string, std::shared_ptr<CTexture>>::iterator iter = mTextures.find(key);

	if (iter == mTextures.end())
		return nullptr;

	return iter->second;
}
