#include "Scene.h"
#include "../Object/Object.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::Update(float DeltaTime)
{
    for (int i = 0; i < (int)ObjectType::END; i++)
    {
        std::vector<std::unique_ptr<CObject>>& typeObjVec = mObjVec[i];

        size_t j = typeObjVec.size();
        while (j > 0)
        {
            --j;
            if (!typeObjVec[j]->GetActive())
            {
                // Active아닌 object는 마지막 요소랑 바꿔준 후 제거
                std::swap(typeObjVec[j], typeObjVec.back());
                typeObjVec.pop_back();
                continue;
            }
            else if (!typeObjVec[j]->GetEnable())
            {
                continue;
            }
            typeObjVec[j]->Update(DeltaTime);
        }
    }
}


void CScene::Render(SDL_Renderer* Renderer)
{
    for (int i = 0; i < (int)ObjectType::END; i++)
    {
        std::vector<std::unique_ptr<CObject>>& typeObjVec = mObjVec[i];

        size_t j = typeObjVec.size();
        while (j > 0)
        {
            --j;
            if (!typeObjVec[j]->GetActive())
            {
                // Active아닌 object는 마지막 요소랑 바꿔준 후 제거
                std::swap(typeObjVec[j], typeObjVec.back());
                typeObjVec.pop_back();
                continue;
            }
            else if (!typeObjVec[j]->GetEnable())
            {
                continue;
            }
            typeObjVec[j]->Render(Renderer);
        }
    }
}