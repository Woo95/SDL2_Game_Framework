#include "Player.h"
#include "../../Core/Input.h"
#include "../Component/MovementComponent.h"
#include "../Component/Collider/BoxCollider.h"
#include "Bullet.h"
#include "../../Scene/Scene.h"
#include "../../Manager/Resource/TextureManager.h"
#include "../../Entity/Component/Sprite/SpriteComponent.h"
#include "../../Resource/Animation.h"

CPlayer::CPlayer() :
    mSpriteComponent(nullptr),
    mMovementComponent(nullptr),
    mCollider(nullptr)
{
}
 
CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    if (!CObject::Init())
        return false;

    // 이동 컴포넌트 만들기
    mMovementComponent = AllocateComponent<CMovementComponent>("Movement", mRootComponent);

    // 충돌체 컴포넌트 만들기
    mCollider = AllocateComponent<CBoxCollider>("playerCollider", mMovementComponent);

    // 위치 설정 (충돌체  컴포넌트)
    CTransform* colliderTrans = mCollider->GetTransform();
    colliderTrans->SetWorldPos(100.f, 100.f);
    colliderTrans->SetWorldScale(50.f, 75.f);
    colliderTrans->SetPivot(0.5f, 0.5f);

    // 스프라이트 컴포넌트 만들기
    mSpriteComponent = AllocateComponent<CSpriteComponent>("playerSprite", mCollider);
    mSpriteComponent->SetTexture("Pasqualina");
    mSpriteComponent->SetAnimation("Pasqualina_Animation");
    mSpriteComponent->GetAnimation()->SetCurrentState(EAnimationState::WALK);
    
    // 위치 설정 (스프라이트 컴포넌트)
    CTransform* spriteTrans = mSpriteComponent->GetTransform();
    spriteTrans->SetWorldPos(100.f, 100.f);
    spriteTrans->SetWorldScale(75.f, 75.f);
    spriteTrans->SetPivot(0.5f, 0.5f);

    // 인풋 설정
    SetupInput();

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CObject::Update(DeltaTime);
}

void CPlayer::LateUpdate(float DeltaTime)
{
    CObject::LateUpdate(DeltaTime);
}

void CPlayer::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);
}

void CPlayer::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
}

void CPlayer::SetupInput()
{
    // 일반 함수 포인터랑은 다르게... 
    // 클래스 멤버 함수 포인터는 클래스 이름까지 적어줘야 되고, 값을 줄 때는 멤버 함수에다 &까지 붙여야 한다. (&CPlayer::MOVE_UP)
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveUp",    EKeyType::Hold, this, &CPlayer::MOVE_UP,    mScene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveDown",  EKeyType::Hold, this, &CPlayer::MOVE_DOWN,  mScene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveLeft",  EKeyType::Hold, this, &CPlayer::MOVE_LEFT,  mScene);
    CInput::GetInst()->AddBindFunction<CPlayer>("MoveRight", EKeyType::Hold, this, &CPlayer::MOVE_RIGHT, mScene);

    CInput::GetInst()->AddBindFunction<CPlayer>("Shoot", EKeyType::Press, this, &CPlayer::SHOOT, mScene);
}

void CPlayer::MOVE_UP()
{
    mMovementComponent->MoveDir(FVector2D::UP);
}
void CPlayer::MOVE_DOWN()
{
    mMovementComponent->MoveDir(FVector2D::DOWN);
}
void CPlayer::MOVE_LEFT()
{
    mMovementComponent->MoveDir(FVector2D::LEFT);

    if (mSpriteComponent)
        mSpriteComponent->SetFlip(SDL_FLIP_HORIZONTAL);
}
void CPlayer::MOVE_RIGHT()
{
    mMovementComponent->MoveDir(FVector2D::RIGHT);   

    if (mSpriteComponent)
        mSpriteComponent->SetFlip(SDL_FLIP_NONE);
}

void CPlayer::SHOOT()
{
    CBullet* bullet = mScene->AllocateObject<CBullet>("bullet");
    bullet->GetTransform()->SetWorldPos(mCollider->GetTransform()->GetWorldPos());
}