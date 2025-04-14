#include "MovementComponent.h"
#include "../../Entity/Object/Object.h"

CMovementComponent::CMovementComponent() :
	mSpeed(500.f),
	mMoveDir(FVector2D::ZERO),
	mFacingDir(FVector2D::ZERO)
{
	mTypeID = typeid(CMovementComponent).hash_code();
}

CMovementComponent::~CMovementComponent()
{
}

bool CMovementComponent::Init()
{
	return CComponent::Init();
}

void CMovementComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	Move(DeltaTime);
}

void CMovementComponent::LateUpdate(float DeltaTime)
{
	CComponent::LateUpdate(DeltaTime);
}

void CMovementComponent::Render(SDL_Renderer* Renderer)
{
	CComponent::Render(Renderer);
}

void CMovementComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMovementComponent>(this);
}

void CMovementComponent::Move(float DeltaTime)
{
	if (mMoveDir != FVector2D::ZERO)
	{
		CTransform* transform = mObject->GetTransform();

		FVector2D movement = mMoveDir.GetNormalize() * mSpeed * DeltaTime;

		transform->SetWorldPos(transform->GetWorldPos() + movement);

		mFacingDir = mMoveDir;

		mMoveDir = FVector2D::ZERO;
	}
}