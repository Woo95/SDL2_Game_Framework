#include "Scene.h"
#include "../Entity/Object/Object.h"
#include "../Core/Timer.h"
#include "../Scene/Collision/SceneCollision.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"

CScene::CScene()
{
    mTextManager = CAssetManager::GetInst()->GetTextureManager();
}

CScene::~CScene()
{
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iter    = mObjMap.begin();
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iterEnd = mObjMap.end();

    for (; iter != iterEnd; iter++)
    {
        std::vector<CObject*>& typeObjVec = iter->second;

        for (CObject* obj : typeObjVec)
        {
            obj->Release();
        }
    }
}

void CScene::Update(float DeltaTime)
{
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iter    = mObjMap.begin();
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iterEnd = mObjMap.end();

    for (; iter != iterEnd; iter++)
    {
        std::vector<CObject*>& typeObjVec = iter->second;

        for (CObject* obj : typeObjVec)
        {
            if (!obj->GetActive())
            {
                obj->Destroy();

                continue;
            }
            else if (!obj->GetEnable())
            {
                continue;
            }
            obj->Update(DeltaTime);
        }
    }
    if (mSceneCollision)
        mSceneCollision->Update(DeltaTime);
}

void CScene::LateUpdate(float DeltaTime)
{
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iter    = mObjMap.begin();
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iterEnd = mObjMap.end();

    for (; iter != iterEnd; iter++)
    {
        std::vector<CObject*>& typeObjVec = iter->second;

        for (size_t j = typeObjVec.size(); j > 0; j--)
        {
            CObject* obj = typeObjVec[j - 1];   // starts from last idx

            if (!obj->GetActive())
            {
                // Active아닌 object는 마지막 요소랑 바꿔준 후 제거
                std::swap(typeObjVec[j - 1], typeObjVec.back());
                typeObjVec.pop_back();

                // 사용된 메모리 반환
                obj->Release();

                continue;
            }
            else if (!obj->GetEnable())
            {
                continue;
            }
            obj->LateUpdate(DeltaTime);
        }
    }
    if (mSceneCollision)
        mSceneCollision->LateUpdate(DeltaTime);
}

void CScene::Render(SDL_Renderer* Renderer)
{
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iter    = mObjMap.begin();
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iterEnd = mObjMap.end();

    for (; iter != iterEnd; iter++)
    {
        std::vector<CObject*>& typeObjVec = iter->second;

        for (CObject* obj : typeObjVec)
        {
            if (!obj->GetActive() || !obj->GetEnable())
            {
                continue;
            }
            obj->Render(Renderer);
        }
    }
    if (mSceneCollision)
        mSceneCollision->Render(Renderer);
}