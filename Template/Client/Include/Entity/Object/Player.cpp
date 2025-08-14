#include "Player.h"
#include "Bullet.h"
#include "../../Core/Input.h"
#include "../Component/MovementComponent.h"
#include "../Component/Collider/BoxCollider.h"
#include "../../Entity/Component/SpriteComponent.h"
#include "../../Resource/Animation.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Camera.h"
#include "../../Entity/Component/WidgetComponent.h"
#include "../../Widget/ProgressBar.h"
#include "../../Entity/Component/Rigidbody.h"
#include "../../Entity/Component/InputComponent.h"

CPlayer::CPlayer() :
    mMovementComponent(nullptr),
    mSpriteComponent(nullptr),
    mColliderComponent(nullptr),
    mRigidbody(nullptr),
    mWidgetComponent(nullptr),
    mInputComponent(nullptr)
{
}
 
CPlayer::~CPlayer()
{
    mInputComponent->DeleteFunctionFromBinder("UP",    this);
    mInputComponent->DeleteFunctionFromBinder("DOWN",  this);
    mInputComponent->DeleteFunctionFromBinder("LEFT",  this);
    mInputComponent->DeleteFunctionFromBinder("RIGHT", this);
    mInputComponent->DeleteFunctionFromBinder("SHOOT", this);
}

bool CPlayer::Init()
{
    // 이동 컴포넌트 설정
    mMovementComponent = AllocateComponent<CMovementComponent>("Movement");

    // 충돌체 컴포넌트 설정
    mColliderComponent = AllocateComponent<CBoxCollider>("collider");
    mColliderComponent->SetProfile("Player");
    mColliderComponent->GetTransform()->SetWorldScale(50.f, 75.f);
    mColliderComponent->GetTransform()->SetPivot(0.5f, 0.5f);

    // 충돌체 콜백 함수 등록
    mColliderComponent->AddCallbackFunc(ECollider::OnCollision::ENTER, this, &CPlayer::KnockBackOpponent);

    // 스프라이트 컴포넌트 설정
    mSpriteComponent = AllocateComponent<CSpriteComponent>("sprite");
    mSpriteComponent->SetTexture("Pasqualina");
    mSpriteComponent->SetAnimation("Pasqualina");
    mSpriteComponent->GetAnimation()->SetState(EAnimationState::WALK);
    mSpriteComponent->GetTransform()->SetWorldScale(75.f, 75.f);
    mSpriteComponent->GetTransform()->SetPivot(0.5f, 0.5f);

    // 리지드바디 컴포넌트 설정
    mRigidbody = AllocateComponent<CRigidbody>("rigidbody");

    // 위젯 컴포넌트 설정
    mWidgetComponent = AllocateComponent<CWidgetComponent>("widget");

    // 프로그레스 바 설정
    CProgressBar* progressBar = CWidgetUtils::AllocateWidget<CProgressBar>("hp");
    progressBar->GetTransform()->SetWorldScale(70.f, 13.f);
    progressBar->GetTransform()->SetPivot(0.5f, 0.5f);
    progressBar->SetColor(EProgBar::State::BACK, 0, 0, 0);
    progressBar->SetTexture("UI");
    progressBar->SetFrame("HpBar");

    // 프로그레스 바 위젯 설정 및 추가
    mWidgetComponent->SetWidget(progressBar);
    progressBar->GetTransform()->SetRelativePos(0.f, 50.f);

    mInputComponent = AllocateComponent<CInputComponent>("input");

    // 컴포넌트들 계층 구조에 추가
    GetComponent()->AddChild(mMovementComponent);
    GetComponent()->AddChild(mSpriteComponent);
    GetComponent()->AddChild(mColliderComponent);
    GetComponent()->AddChild(mRigidbody);
    GetComponent()->AddChild(mWidgetComponent);
    GetComponent()->AddChild(mInputComponent);

    // 오브젝트 위치 설정
    GetTransform()->SetWorldPos(400.f, 200.f);

    // 인풋 설정
    SetupInput();

    // 부모 클래스 초기화
    return CObject::Init();
}

void CPlayer::Update(float deltaTime)
{
	CObject::Update(deltaTime);
}

void CPlayer::LateUpdate(float deltaTime)
{
    CObject::LateUpdate(deltaTime);
}

void CPlayer::Render(SDL_Renderer* renderer)
{
    CObject::Render(renderer);
}

void CPlayer::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
}

void CPlayer::SetupInput()
{
    // 클래스 멤버 함수 포인터는 일반 함수와 다르게 "&클래스명::함수" 이렇게 해야한다. (ex: &CPlayer::MOVE_UP)

    mInputComponent->AddFunctionToBinder("UP",    this, &CPlayer::MOVE_UP);
    mInputComponent->AddFunctionToBinder("DOWN",  this, &CPlayer::MOVE_DOWN);
    mInputComponent->AddFunctionToBinder("LEFT",  this, &CPlayer::MOVE_LEFT);
    mInputComponent->AddFunctionToBinder("RIGHT", this, &CPlayer::MOVE_RIGHT);
    mInputComponent->AddFunctionToBinder("SHOOT", this, &CPlayer::SHOOT);

    mInputComponent->AddInputToBinder("UP",    SDL_SCANCODE_W,  EKey::State::HOLD);
    mInputComponent->AddInputToBinder("DOWN",  SDL_SCANCODE_S,  EKey::State::HOLD);
    mInputComponent->AddInputToBinder("LEFT",  SDL_SCANCODE_A,  EKey::State::HOLD);
    mInputComponent->AddInputToBinder("RIGHT", SDL_SCANCODE_D,  EKey::State::HOLD);
    mInputComponent->AddInputToBinder("SHOOT", SDL_BUTTON_LEFT, EKey::State::PRESS);
}

void CPlayer::MOVE_UP()
{
    mMovementComponent->AddMoveDir(FVector2D::UP);
}
void CPlayer::MOVE_DOWN()
{
    mMovementComponent->AddMoveDir(FVector2D::DOWN);
}
void CPlayer::MOVE_LEFT()
{
    mMovementComponent->AddMoveDir(FVector2D::LEFT);

    if (mSpriteComponent)
        mSpriteComponent->SetFlip(SDL_FLIP_HORIZONTAL);
}
void CPlayer::MOVE_RIGHT()
{
    mMovementComponent->AddMoveDir(FVector2D::RIGHT);   

    if (mSpriteComponent)
        mSpriteComponent->SetFlip(SDL_FLIP_NONE);
}

void CPlayer::KnockBackOpponent(CCollider* self, CCollider* other)
{
    if (CRigidbody* rb = other->GetObject()->GetComponent<CRigidbody>())
    {
        const FVector2D& facingDir = mMovementComponent->GetFacingDir();
        if (facingDir != FVector2D::ZERO)
        {
            rb->AddImpulse(facingDir.GetNormalize() * 50000.0f/*knockbackPower*/);
        }
    }
}

void CPlayer::SHOOT()
{
    CBullet* bullet = mScene->InstantiateObject<CBullet>("bullet", ELayer::Type::PROJECTILE);

    bullet->GetTransform()->SetWorldPos(mScene->GetCamera()->GetWorldPos(CInput::GetInst()->GetMousePos()));
}