#include "Layer.h"
#include "../Entity/Object/Object.h"
#include "../Entity/Component/SpriteComponent.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
    for (CObject* obj : mObjects)
    {
        obj->Release();
    }
}

void CLayer::Update(float deltaTime)
{
    for (CObject* obj : mObjects)
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
        obj->Update(deltaTime);
    }
}

void CLayer::LateUpdate(float deltaTime)
{
    for (size_t i = mObjects.size(); i > 0; i--)
    {
        CObject* obj = mObjects[i - 1];

        if (!obj->GetActive())
        {
            // Active아닌 object는 마지막 요소랑 바꿔준 후 제거
            std::swap(mObjects[i - 1], mObjects.back());
            mObjects.pop_back();

            // 사용된 메모리 반환
            obj->Release();

            continue;
        }
        else if (!obj->GetEnable())
        {
            continue;
        }
        obj->LateUpdate(deltaTime);
    }
}

void CLayer::Render(SDL_Renderer* renderer)
{
    switch (mSort)
    {
    case ESort::Type::NONE:
        break;
    case ESort::Type::Y:
        std::sort(mObjects.begin(), mObjects.end(), SortY);
        break;
    }

    for (CObject* obj : mObjects)
    {
        if (!obj->GetActive() || !obj->GetEnable())
            continue;

        obj->Render(renderer);
    }
}

bool CLayer::SortY(CObject* objA, CObject* objB)
{
    return objA->GetTransform()->GetWorldPos().y < objB->GetTransform()->GetWorldPos().y;
}