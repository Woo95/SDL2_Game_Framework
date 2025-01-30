#include "Bullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/Collider/CircleCollider.h"
#include "../../Entity/Component/Sprite/SpriteComponent.h"

CBullet::CBullet() :
    mMovementComponent(nullptr),
    mDestroyTime(0)
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	if (!CObject::Init())
		return false;

    // 이동 컴포넌트 만들기
    mMovementComponent = AllocateComponent<CMovementComponent>("Movement", mRootComponent);

    // 충돌체 컴포넌트 만들기
    CCircleCollider* collider = AllocateComponent<CCircleCollider>("collider", mMovementComponent);

    // 위치 설정 (충돌체 컴포넌트)
    CTransform* colliderTrans = collider->GetTransform();
    colliderTrans->SetWorldScale(25.f, 25.f);
    colliderTrans->SetPivot(0.5f, 0.5f);

    // 스프라이트 컴포넌트 만들기
    CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite", collider);
    sprite->SetTexture("Bullet");

    // 위치 설정 (스프라이트 컴포넌트)
    CTransform* spriteTrans = sprite->GetTransform();
    spriteTrans->SetWorldPos(colliderTrans->GetWorldPos());
    spriteTrans->SetWorldScale(25.f, 25.f);
    spriteTrans->SetPivot(0.5f, 0.5f);


    return true;
}

void CBullet::Update(float DeltaTime)
{
	CObject::Update(DeltaTime);

    //mMovementComponent->MoveDir(FVector2D::RIGHT);

    mDestroyTime += DeltaTime;

    if (mDestroyTime >= 5.0f)
        Destroy();
}

void CBullet::LateUpdate(float DeltaTime)
{
    CObject::LateUpdate(DeltaTime);
}

void CBullet::Render(SDL_Renderer* Renderer)
{
	CObject::Render(Renderer);
}

void CBullet::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CBullet>(this);
}