#include "Monster.h"
#include "../Component/Collider/BoxCollider.h"
#include "../../Entity/Component/SpriteComponent.h"
#include "../../Resource/Animation.h"
#include "../../Entity/Component/Rigidbody.h"

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

    CCollider* collider = AllocateComponent<CBoxCollider>("collider", mRootComponent);
    collider->SetProfile("Monster");
    collider->GetTransform()->SetWorldScale(50.f, 75.f);
    collider->GetTransform()->SetPivot(0.5f, 0.5f);

    CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite", collider);
    sprite->SetTexture("Imelda");
    sprite->SetAnimation("Imelda");
    sprite->GetAnimation()->SetCurrentState(EAnimationState::WALK);

    sprite->GetTransform()->SetWorldScale(75.f, 75.f);
    sprite->GetTransform()->SetPivot(0.5f, 0.5f);

    CRigidbody* rb = AllocateComponent<CRigidbody>("rigidbody", sprite);

    GetTransform()->SetWorldPos(800.f, 200.f);

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