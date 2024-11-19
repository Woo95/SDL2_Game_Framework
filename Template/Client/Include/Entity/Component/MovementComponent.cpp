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