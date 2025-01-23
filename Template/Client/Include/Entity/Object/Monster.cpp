#include "Monster.h"
#include "../../Manager/MemoryPoolManager.h"
#include "../Component/Collider/BoxCollider.h"

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

void CMonster::LateUpdate(float DeltaTime)
{
    CObject::LateUpdate(DeltaTime);
}

void CMonster::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);
}

void CMonster::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CMonster>(this);
}