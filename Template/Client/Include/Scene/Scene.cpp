#include "Scene.h"
#include "Extension/Camera.h"
#include "Extension/SceneCollision.h"
#include "Extension/SceneUI.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/TextureManager.h"
#include "../Manager/Data/Resource/FontManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CScene::CScene() :
	mCamera(nullptr),
    mSceneCollision(nullptr),
    mSceneUI(nullptr)
{
    mLayers.resize(ELayer::Type::MAX);

    for (int i = 0; i < ELayer::Type::MAX; i++)
    {
        mLayers[i] = CMemoryPoolManager::GetInst()->Allocate<CLayer>();
    }
}

CScene::~CScene()
{
    for (CLayer* layer : mLayers)
    {
        CMemoryPoolManager::GetInst()->DeallocateButKeepPool<CLayer>(layer);
    }
}

void CScene::Update(float deltaTime)
{
    for (CLayer* layer : mLayers)
        layer->Update(deltaTime);

	if (mCamera)
		mCamera->Update(deltaTime);

    if (mSceneCollision)
		mSceneCollision->Update(deltaTime);

    if (mSceneUI)
        mSceneUI->Update(deltaTime);
}

void CScene::LateUpdate(float deltaTime)
{
    for (CLayer* layer : mLayers)
        layer->LateUpdate(deltaTime);

    if (mSceneUI)
        mSceneUI->LateUpdate(deltaTime);
}

void CScene::Render(SDL_Renderer* renderer)
{
    for (CLayer* layer : mLayers)
        layer->Render(renderer);

    if (mSceneCollision)
        mSceneCollision->Render(renderer);

    if (mSceneUI)
        mSceneUI->Render(renderer);
}

void CScene::LoadTexture(const std::string& key, const char* fileName)
{
    CTextureManager* TM = CAssetManager::GetInst()->GetTextureManager();

    mTextures.emplace_back(TM->LoadTexture(key, fileName));
}

void CScene::LoadFont(const std::string& key, const char* fileName, int fontSize)
{
    CFontManager* FM = CAssetManager::GetInst()->GetFontManager();

    mFonts.emplace_back(FM->LoadFont(key, fileName, fontSize));
}

void CScene::LoadSFX(const std::string& key, const char* fileName)
{
    CSoundManager* SM = CAssetManager::GetInst()->GetSoundManager();
    
    mSFXs.emplace_back(SM->LoadSound<CSFX>(key, fileName));
}

void CScene::LoadBGM(const std::string& key, const char* fileName)
{
    CSoundManager* SM = CAssetManager::GetInst()->GetSoundManager();

    mBGMs.emplace_back(SM->LoadSound<CBGM>(key, fileName));
}