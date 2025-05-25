#include "Bullet.h"
#include "../Component/MovementComponent.h"
#include "../Component/Collider/CircleCollider.h"
#include "../../Entity/Component/SpriteComponent.h"

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
    // 이동 컴포넌트 설정
    mMovementComponent = AllocateComponent<CMovementComponent>("Movement");
    GetComponent()->AddChild(mMovementComponent);

    // 충돌체 컴포넌트 설정
    CCollider* collider = AllocateComponent<CCircleCollider>("collider");
    collider->SetProfile("Bullet");
    collider->GetTransform()->SetWorldScale(25.f, 25.f);
    collider->GetTransform()->SetPivot(0.5f, 0.5f);

    // 이동 컴포넌트에 충돌체 추가
    mMovementComponent->AddChild(collider);

    // 스프라이트 컴포넌트 설정
    CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite");
    sprite->SetTexture("Bullet");
    sprite->SetFrame("Bullet");

    // 스프라이트 위치 설정
    sprite->GetTransform()->SetWorldPos(collider->GetTransform()->GetWorldPos());
    sprite->GetTransform()->SetWorldScale(25.f, 25.f);
    sprite->GetTransform()->SetPivot(0.5f, 0.5f);

    // 충돌체에 스프라이트 추가
    collider->AddChild(sprite);

    // 초기화 완료 후 부모 클래스 초기화 호출
    return CObject::Init();
}

void CBullet::Update(float deltaTime)
{
	CObject::Update(deltaTime);

    //mMovementComponent->AddMoveDir(FVector2D::RIGHT);

    mDestroyTime += deltaTime;

    if (mDestroyTime >= 5.0f)
        Destroy();
}

void CBullet::LateUpdate(float deltaTime)
{
    CObject::LateUpdate(deltaTime);
}

void CBullet::Render(SDL_Renderer* renderer)
{
	CObject::Render(renderer);
}

void CBullet::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CBullet>(this);
}