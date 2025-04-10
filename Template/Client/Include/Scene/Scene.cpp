#include "Scene.h"
#include "../Scene/Collision/SceneCollision.h"
#include "Camera.h"
#include "../Scene/UI/SceneUI.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/FontManager.h"
#include "../Manager/Resource/SoundManager.h"

CScene::CScene() :
    mSceneCollision(nullptr),
    mCamera(nullptr),
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
    UnloadResources();
}

void CScene::Update(float DeltaTime)
{
    for (CLayer* layer : mLayers)
        layer->Update(DeltaTime);

    if (mSceneCollision)
        mSceneCollision->Update(DeltaTime);

    if (mCamera)
        mCamera->Update(DeltaTime);

    if (mSceneUI)
        mSceneUI->Update(DeltaTime);
}

void CScene::LateUpdate(float DeltaTime)
{
    for (CLayer* layer : mLayers)
        layer->LateUpdate(DeltaTime);

    if (mSceneUI)
        mSceneUI->LateUpdate(DeltaTime);
}

void CScene::Render(SDL_Renderer* Renderer)
{
    for (CLayer* layer : mLayers)
        layer->Render(Renderer);

    if (mSceneCollision)
        mSceneCollision->Render(Renderer);

    if (mSceneUI)
        mSceneUI->Render(Renderer);
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

void CScene::UnloadResources()
{
    mTextures.clear();
    mFonts.clear();
    mSFXs.clear();
    mBGMs.clear();
}