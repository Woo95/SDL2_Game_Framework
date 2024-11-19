#include "Player.h"
#include "../../Core/Input.h"
#include "../Component/MovementComponent.h"
#include "../Component/Rectangle.h"

CPlayer::CPlayer() :
    mMovementComponent(nullptr)
{
}
 
CPlayer::~CPlayer()
{
    DeletePoolAndSync<CRectangle>();
}

bool CPlayer::Init()
{
    if (!CObject::Init())
        return false;

    // 이동 컴포넌트 만들기
    mMovementComponent = CreateComponent<CMovementComponent>("Movement");

    // 도형 컴포넌트 만들기
    CreatePoolAndSync<CRectangle>(3);

    CComponent* parent = AllocateComponent<CRectangle>("Parent", mMovementComponent);
    parent->GetTransform()->SetWorldPos(100.f, 100.f);
    parent->GetTransform()->SetWorldScale(200.f, 200.f);
    parent->GetTransform()->SetPivot(0.5f, 0.5f);

    CComponent* child = AllocateComponent<CRectangle>("Child", parent);
    child->GetTransform()->SetRelativePos(0.f, 0.f);
    child->GetTransform()->SetWorldScale(100.f, 100.f);
    child->GetTransform()->SetPivot(0.5f, 0.5f);


    CComponent* childChild = AllocateComponent<CRectangle>("ChildChild", child);
    childChild->GetTransform()->SetRelativePos(0.f, 0.f);
    childChild->GetTransform()->SetWorldScale(50.f, 50.f);
    childChild->GetTransform()->SetPivot(0.5f, 0.5f);

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