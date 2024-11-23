#include "MovementComponent.h"

CMovementComponent::CMovementComponent() :
	mSpeed(500.f), 
	mDirection(FVector2D::ZERO)
{
}

void CMovementComponent::Update(float DeltaTime)
{
	Move(DeltaTime);
}

bool CMovementComponent::Release()
{
	if (CMemoryPoolManager::GetInst()->HasPool<CMovementComponent>())
	{
		CMemoryPoolManager::GetInst()->Deallocate<CMovementComponent>(this);
		return true;
	}
	return false;
}

void CMovementComponent::Move(float DeltaTime)
{
	if (mDirection != FVector2D::ZERO)
	{
		CTransform* transform = GetTransform();

		FVector2D movement = mDirection.GetNormalize() * mSpeed * DeltaTime;

		transform->SetWorldPos(transform->GetWorldPos() + movement);

		mDirection = FVector2D::ZERO;
	}
}