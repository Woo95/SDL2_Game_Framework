#include "Bullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/BoxCollider.h"

CBullet::CBullet() :
    mMovementComponent(nullptr),
    mCollider(nullptr),
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

    // 도형 컴포넌트 만들기
    mCollider = AllocateComponent<CBoxCollider>("BulletCollider", mMovementComponent);
    CTransform* bulletTransform = mCollider->GetTransform();
    bulletTransform->SetWorldScale(25.f, 25.f);
    bulletTransform->SetPivot(0.5f, 0.5f);

    return true;
}

void CBullet::Update(float DeltaTime)
{
	CObject::Update(DeltaTime);

    //mMovementComponent->MoveDir(FVector2D::RIGHT);
    mDestroyTime += DeltaTime;

    if (mDestroyTime >= 1.0f)
        Destroy();
}

void CBullet::Render(SDL_Renderer* Renderer)
{
	CObject::Render(Renderer);
}

void CBullet::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CBullet>(this);
}