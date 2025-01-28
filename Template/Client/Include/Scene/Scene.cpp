#include "Scene.h"
#include "../Scene/Collision/SceneCollision.h"

CScene::CScene()
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
        CMemoryPoolManager::GetInst()->DeallocateKeepPool<CLayer>(layer);
    }
}

void CScene::Update(float DeltaTime)
{
    for (CLayer* layer : mLayers)
        layer->Update(DeltaTime);

    if (mSceneCollision)
        mSceneCollision->Update(DeltaTime);
}

void CScene::LateUpdate(float DeltaTime)
{
    for (CLayer* layer : mLayers)
        layer->LateUpdate(DeltaTime);

    if (mSceneCollision)
        mSceneCollision->LateUpdate(DeltaTime);
}

void CScene::Render(SDL_Renderer* Renderer)
{
    for (CLayer* layer : mLayers)
        layer->Render(Renderer);

    if (mSceneCollision)
        mSceneCollision->Render(Renderer);
}