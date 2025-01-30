#include "Monster.h"
#include "../Component/Collider/BoxCollider.h"
#include "../../Entity/Component/Sprite/SpriteComponent.h"
#include "../../Resource/Animation.h"

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

    CComponent* collider = AllocateComponent<CBoxCollider>("collider", mRootComponent);
    collider->GetTransform()->SetWorldScale(50.f, 75.f);
    collider->GetTransform()->SetPivot(0.5f, 0.5f);

    CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite", collider);
    sprite->SetTexture("Antonio");
    sprite->SetAnimation("Antonio_Animation");
    sprite->GetAnimation()->SetCurrentState(EAnimationState::NONE);
    
    sprite->GetTransform()->SetWorldScale(75.f, 75.f);
    sprite->GetTransform()->SetPivot(0.5f, 0.5f);

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