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

CPlayer::CPlayer() :
    mMovementComponent(nullptr),
    mColliderComponent(nullptr),
    mSpriteComponent(nullptr),
    mWidgetComponent(nullptr)
{
}
 
CPlayer::~CPlayer()
{
    CInput::GetInst()->DeleteFunctionFromBinder("UP",    this);
    CInput::GetInst()->DeleteFunctionFromBinder("DOWN",  this);
    CInput::GetInst()->DeleteFunctionFromBinder("LEFT",  this);
    CInput::GetInst()->DeleteFunctionFromBinder("RIGHT", this);
    CInput::GetInst()->DeleteFunctionFromBinder("SHOOT", this);
}

bool CPlayer::Init()
{
    if (!CObject::Init())
        return false;

    // 이동 컴포넌트 만들기
    mMovementComponent = AllocateComponent<CMovementComponent>("Movement", mRootComponent);

    // 충돌체 컴포넌트 만들기
    mColliderComponent = AllocateComponent<CBoxCollider>("collider", mMovementComponent);
    mColliderComponent->SetProfile("Player");

    // 위치 설정 (충돌체 컴포넌트)
    CTransform* colliderTrans = mColliderComponent->GetTransform();
    colliderTrans->SetWorldScale(50.f, 75.f);
    colliderTrans->SetPivot(0.5f, 0.5f);

    // 충돌체 함수 등록
    mColliderComponent->AddCallbackFunc(ECollider::OnCollision::ENTER, this, &CPlayer::KnockBackOpponent);

    // 스프라이트 컴포넌트 만들기
    mSpriteComponent = AllocateComponent<CSpriteComponent>("sprite", mColliderComponent);
    mSpriteComponent->SetTexture("Pasqualina");
    mSpriteComponent->SetAnimation("Pasqualina");
    mSpriteComponent->GetAnimation()->SetCurrentState(EAnimationState::WALK);
    
    // 위치 설정 (스프라이트 컴포넌트)
    CTransform* spriteTrans = mSpriteComponent->GetTransform();
    spriteTrans->SetWorldScale(75.f, 75.f);
    spriteTrans->SetPivot(0.5f, 0.5f);

    // 리지드바디 컴포넌트 만들기
    CRigidbody* rb = AllocateComponent<CRigidbody>("rigidbody", mSpriteComponent);

    /////////////////////////////////////////////////////////////////////////////////////////////

    // 위젯 컴포넌트 만들기
    mWidgetComponent = AllocateComponent<CWidgetComponent>("widget", mSpriteComponent);

    // 프로그레스 바 생성 및 설정
    CProgressBar* progressBar = CWidgetUtils::AllocateWidget<CProgressBar>("hp");
    progressBar->GetTransform()->SetWorldScale(70.f, 13.f);
    progressBar->GetTransform()->SetPivot(0.5f, 0.5f);
    progressBar->SetColor(EProgBar::State::BACK, 0, 0, 0);

    // 프로그레스 바 텍스쳐 및 프레임 설정
    progressBar->SetTexture("UI");
    progressBar->SetFrame("HpBar");

    // 위젯 자식으로 프로그레스 바 추가 및 위젯 설정
    mWidgetComponent->SetWidget(progressBar);
    progressBar->GetTransform()->SetRelativePos(0.f, 50.f);

    // 오브젝트 위치 설정
    GetTransform()->SetWorldPos(400.f, 200.f);

    // 인풋 설정
    SetupInput();

	return true;
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

    CInput::GetInst()->AddFunctionToBinder("UP",    this, &CPlayer::MOVE_UP);
    CInput::GetInst()->AddFunctionToBinder("DOWN",  this, &CPlayer::MOVE_DOWN);
    CInput::GetInst()->AddFunctionToBinder("LEFT",  this, &CPlayer::MOVE_LEFT);
    CInput::GetInst()->AddFunctionToBinder("RIGHT", this, &CPlayer::MOVE_RIGHT);
    CInput::GetInst()->AddFunctionToBinder("SHOOT", this, &CPlayer::SHOOT);
    
    CInput::GetInst()->AddInputToBinder("UP",    SDL_SCANCODE_W,  EKey::State::HOLD);
    CInput::GetInst()->AddInputToBinder("DOWN",  SDL_SCANCODE_S,  EKey::State::HOLD);
    CInput::GetInst()->AddInputToBinder("LEFT",  SDL_SCANCODE_A,  EKey::State::HOLD);
    CInput::GetInst()->AddInputToBinder("RIGHT", SDL_SCANCODE_D,  EKey::State::HOLD);
    CInput::GetInst()->AddInputToBinder("SHOOT", SDL_BUTTON_LEFT, EKey::State::PRESS);
}

void CPlayer::MOVE_UP()
{
    mMovementComponent->AddMoveInput(FVector2D::UP);
}
void CPlayer::MOVE_DOWN()
{
    mMovementComponent->AddMoveInput(FVector2D::DOWN);
}
void CPlayer::MOVE_LEFT()
{
    mMovementComponent->AddMoveInput(FVector2D::LEFT);

    if (mSpriteComponent)
        mSpriteComponent->SetFlip(SDL_FLIP_HORIZONTAL);
}
void CPlayer::MOVE_RIGHT()
{
    mMovementComponent->AddMoveInput(FVector2D::RIGHT);   

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
    CBullet* bullet = mScene->AllocateObject<CBullet>("bullet", ELayer::Type::PROJECTILE);

    bullet->GetTransform()->SetWorldPos(mScene->GetCamera()->GetWorldPos(CInput::GetInst()->GetMousePos()));
}