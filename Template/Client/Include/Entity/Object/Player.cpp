#include "Player.h"
#include "Bullet.h"
#include "../../Core/Input.h"
#include "../Component/MovementComponent.h"
#include "../Component/Collider/BoxCollider.h"
#include "../../Entity/Component/Sprite/SpriteComponent.h"
#include "../../Resource/Animation.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Camera.h"

CPlayer::CPlayer() :
    mMovementComponent(nullptr),
    mColliderComponent(nullptr),
    mSpriteComponent(nullptr)
{
}
 
CPlayer::~CPlayer()
{
    CInput::GetInst()->DeleteFunctionFromKey<CPlayer>(SDL_SCANCODE_W, EKey::State::HOLD, this);
    CInput::GetInst()->DeleteFunctionFromKey<CPlayer>(SDL_SCANCODE_A, EKey::State::HOLD, this);
    CInput::GetInst()->DeleteFunctionFromKey<CPlayer>(SDL_SCANCODE_S, EKey::State::HOLD, this);
    CInput::GetInst()->DeleteFunctionFromKey<CPlayer>(SDL_SCANCODE_D, EKey::State::HOLD, this);

    CInput::GetInst()->DeleteFunctionFromMouse<CPlayer>(SDL_BUTTON_LEFT, EKey::State::HOLD, this);
}

bool CPlayer::Init()
{
    if (!CObject::Init())
        return false;

    // 이동 컴포넌트 만들기
    mMovementComponent = AllocateComponent<CMovementComponent>("Movement", mRootComponent);

    // 충돌체 컴포넌트 만들기
    mColliderComponent = AllocateComponent<CBoxCollider>("collider", mMovementComponent);

    // 위치 설정 (충돌체 컴포넌트)
    CTransform* colliderTrans = mColliderComponent->GetTransform();
    colliderTrans->SetWorldScale(50.f, 75.f);
    colliderTrans->SetPivot(0.5f, 0.5f);

    // 스프라이트 컴포넌트 만들기
    mSpriteComponent = AllocateComponent<CSpriteComponent>("sprite", mColliderComponent);
    mSpriteComponent->SetTexture("Pasqualina");
    mSpriteComponent->SetAnimation("Pasqualina");
    mSpriteComponent->GetAnimation()->SetCurrentState(EAnimationState::WALK);
    
    // 위치 설정 (스프라이트 컴포넌트)
    CTransform* spriteTrans = mSpriteComponent->GetTransform();
    spriteTrans->SetWorldScale(75.f, 75.f);
    spriteTrans->SetPivot(0.5f, 0.5f);

    // 오브젝트 위치 설정
    GetTransform()->SetWorldPos(400.f, 200.f);

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
    CInput::GetInst()->AddFunctionToKey<CPlayer>(false, false, false, SDL_SCANCODE_W, EKey::State::HOLD, this, &CPlayer::MOVE_UP,    mScene);
    CInput::GetInst()->AddFunctionToKey<CPlayer>(false, false, false, SDL_SCANCODE_S, EKey::State::HOLD, this, &CPlayer::MOVE_DOWN,  mScene);
    CInput::GetInst()->AddFunctionToKey<CPlayer>(false, false, false, SDL_SCANCODE_A, EKey::State::HOLD, this, &CPlayer::MOVE_LEFT,  mScene);
    CInput::GetInst()->AddFunctionToKey<CPlayer>(false, false, false, SDL_SCANCODE_D, EKey::State::HOLD, this, &CPlayer::MOVE_RIGHT, mScene);

    CInput::GetInst()->AddFunctionToMouse<CPlayer>(false, false, false, SDL_BUTTON_LEFT, EKey::State::HOLD, this, &CPlayer::SHOOT, mScene);
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
    CBullet* bullet = mScene->AllocateObject<CBullet>("bullet", ELayer::Type::PROJECTILE);

    bullet->GetTransform()->SetWorldPos(mScene->GetCamera()->GetWorldPos(CInput::GetInst()->GetMousePos()));
}