#include "Player.h"
#include "../../Core/Input.h"
#include "../Component/MovementComponent.h"
#include "../Component/Rectangle.h"
#include "Bullet.h"
#include "../../Scene/Scene.h"

CPlayer::CPlayer() :
    mMovementComponent(nullptr),
    mPlayer(nullptr)
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
    mMovementComponent = CreateComponent<CMovementComponent>("Movement", mRootComponent);

    // 도형 컴포넌트 만들기
    mPlayer = AllocateComponent<CRectangle>("Player", mMovementComponent);
    CTransform* playerTransform = mPlayer->GetTransform();
    playerTransform->SetWorldPos(100.f, 100.f);
    playerTransform->SetWorldScale(200.f, 200.f);
    playerTransform->SetPivot(0.5f, 0.5f);

    CComponent* child = AllocateComponent<CRectangle>("Child", mPlayer);
    CTransform* childTransform = child->GetTransform();
    childTransform->SetRelativePos(0.f, 0.f);
    childTransform->SetWorldScale(100.f, 100.f);
    childTransform->SetPivot(0.5f, 0.5f);

    CComponent* childChild = AllocateComponent<CRectangle>("ChildChild", child);
    CTransform* childChildTransform = childChild->GetTransform();
    childChildTransform->SetRelativePos(0.f, 0.f);
    childChildTransform->SetWorldScale(50.f, 50.f);
    childChildTransform->SetPivot(0.5f, 0.5f);

    // 인풋 설정
    SetupInput();

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CObject::Update(DeltaTime);
}

void CPlayer::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);
}

bool CPlayer::Release()
{
    if (CMemoryPoolManager::GetInst()->HasPool<CPlayer>())
    {
        CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
        return true;
    }
    return false;
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
}
void CPlayer::MOVE_RIGHT()
{
    mMovementComponent->MoveDir(FVector2D::RIGHT);
}

void CPlayer::SHOOT()
{
    CBullet* bullet = mScene->CreateObject<CBullet>("bullet");
    bullet->GetTransform()->SetWorldPos(mPlayer->GetTransform()->GetWorldPos());
}