#include "Scene.h"
#include "../Entity/Object/Object.h"
#include "../Core/Timer.h"
#include "../Scene/Collision/SceneCollision.h"

CScene::~CScene()
{
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iter    = mObjMap.begin();
    std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iterEnd = mObjMap.end();

    for (; iter != iterEnd; iter++)
    {
        std::vector<CObject*>& typeObjVec = iter->second;

        for (size_t j = typeObjVec.size(); j > 0; j--)
        {
            CObject* obj = typeObjVec[j - 1];   // starts from last idx

            // 제거해야할 메모리를 가비지 컬렉터에 추가
            CMemoryReleaseManager::GetInst()->AddGarbage(obj);
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

        for (size_t j = typeObjVec.size(); j > 0; j--)
        {
            CObject* obj = typeObjVec[j - 1];   // starts from last idx

            if (!obj->GetActive())
            {
                // Active아닌 object는 마지막 요소랑 바꿔준 후 제거
                std::swap(typeObjVec[j - 1], typeObjVec.back());
                typeObjVec.pop_back();

                // 제거해야할 메모리를 가비지 컬렉터에 추가
                CMemoryReleaseManager::GetInst()->AddGarbage(obj);

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

void CScene::Render(SDL_Renderer* Renderer)
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

                // 제거해야할 메모리를 가비지 컬렉터에 추가
                CMemoryReleaseManager::GetInst()->AddGarbage(obj);

                continue;
            }
            else if (!obj->GetEnable())
            {
                continue;
            }
            obj->Render(Renderer);
        }
    }
    if (mSceneCollision)
        mSceneCollision->Render(Renderer);
}