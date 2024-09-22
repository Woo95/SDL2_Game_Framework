#include "Scene.h"
#include "../Object/Object.h"

CScene::CScene()
{
}

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

            if (!obj->Release())
            {
                SAFE_DELETE(obj);
            }
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
                std::swap(obj, typeObjVec.back());
                typeObjVec.pop_back();

                // 사용된 메모리 삭제 또는 반환
                if (!obj->Release())
                {
                    SAFE_DELETE(obj);
                }
                continue;
            }
            else if (!obj->GetEnable())
            {
                continue;
            }
            obj->Update(DeltaTime);
        }
    }
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
                std::swap(obj, typeObjVec.back());
                typeObjVec.pop_back();

                // 사용된 메모리 삭제 또는 반환
                if (!obj->Release())
                {
                    SAFE_DELETE(obj);
                }
                continue;
            }
            else if (!obj->GetEnable())
            {
                continue;
            }
            obj->Render(Renderer);
        }
    }
}