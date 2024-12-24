#include "Bullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/BoxCollider.h"

CBullet::CBullet() :
    mMovementComponent(nullptr),
    mCollider(nullptr),
    mDestroyTime(0)
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
        SetActive(false);
}

void CBullet::Render(SDL_Renderer* Renderer)
{
	CObject::Render(Renderer);
}

bool CBullet::Release()
{
    if (CMemoryPoolManager::GetInst()->HasPool<CBullet>())
    {
        CMemoryPoolManager::GetInst()->Deallocate<CBullet>(this);
        return true;
    }
    return false;
}