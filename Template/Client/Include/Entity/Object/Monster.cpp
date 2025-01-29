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
    collider->GetTransform()->SetWorldPos(800, 200.f);
    collider->GetTransform()->SetWorldScale(50.f, 75.f);
    collider->GetTransform()->SetPivot(0.5f, 0.5f);

    mSpriteComponent = AllocateComponent<CSpriteComponent>("sprite", collider);
    mSpriteComponent->SetTexture("Antonio");
    mSpriteComponent->SetAnimation("Antonio_Animation");
    mSpriteComponent->GetAnimation()->SetCurrentState(EAnimationState::NONE);

    mSpriteComponent->GetTransform()->SetWorldPos(collider->GetTransform()->GetWorldPos());
    mSpriteComponent->GetTransform()->SetWorldScale(75.f, 75.f);
    mSpriteComponent->GetTransform()->SetPivot(0.5f, 0.5f);

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