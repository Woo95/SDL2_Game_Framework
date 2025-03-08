#include "Scene.h"
#include "../Scene/Collision/SceneCollision.h"
#include "Camera.h"
#include "../Scene/UI/SceneUI.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/GameManager.h"

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
    mCamera = new CCamera;
    mCamera->SetResolution(CGameManager::GetInst()->GetResolution());
}

CScene::~CScene()
{
    for (CLayer* layer : mLayers)
    {
        CMemoryPoolManager::GetInst()->DeallocateButKeepPool<CLayer>(layer);
    }
    SAFE_DELETE(mCamera);
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

    TM->LoadTexture(key, fileName);
    mTextureKeys.insert(key);
}

void CScene::UnloadTextures()
{
    CTextureManager* TM = CAssetManager::GetInst()->GetTextureManager();

    for (const std::string& key : mTextureKeys)
    {
        TM->UnloadTexture(key);
    }
}