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

void CMovementComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	Move(deltaTime);
}

void CMovementComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMovementComponent>(this);
}

void CMovementComponent::Move(float deltaTime)
{
	if (mMoveDir != FVector2D::ZERO)
	{
		CTransform* transform = mObject->GetTransform();

		FVector2D movement = mMoveDir.GetNormalize() * mSpeed * deltaTime;

		transform->SetWorldPos(transform->GetWorldPos() + movement);

		mFacingDir = mMoveDir;

		mMoveDir = FVector2D::ZERO;
	}
}