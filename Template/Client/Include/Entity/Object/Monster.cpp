#include "Monster.h"
#include "../../Manager/MemoryPoolManager.h"
#include "../Component/BoxCollider.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
    if (!CObject::Init())
        return false;

    CComponent* monster = AllocateComponent<CBoxCollider>("Monster", mRootComponent);
    monster->GetTransform()->SetWorldPos(800, 200.f);
    monster->GetTransform()->SetWorldScale(100.f, 100.f);
    monster->GetTransform()->SetPivot(0.5f, 0.5f);

    return true;
}

void CMonster::Update(float DeltaTime)
{
    CObject::Update(DeltaTime);
}

void CMonster::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);
}

bool CMonster::Release()
{
    if (CMemoryPoolManager::GetInst()->HasPool<CMonster>())
    {
        CMemoryPoolManager::GetInst()->Deallocate<CMonster>(this);
        return true;
    }
    return false;
}