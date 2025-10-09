#include "MovementComponent.h"
#include "../../Entity/Object/Object.h"

CMovementComponent::CMovementComponent() :
	mSpeed(500.f),
	mAccumulatedDir(FVector2D::ZERO),
	mPrevMoveDir(FVector2D::ZERO),
	mCurrMoveDir(FVector2D::ZERO)
{
	mTypeID = typeid(CMovementComponent).hash_code();
}

CMovementComponent::~CMovementComponent()
{
}

void CMovementComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	if (mAccumulatedDir != FVector2D::ZERO)
	{
		mCurrMoveDir = mAccumulatedDir.GetNormalize();

		FVector2D movement = mCurrMoveDir * mSpeed * deltaTime;

		if (CTransform* transform = mObject->GetTransform())
			transform->SetWorldPos(transform->GetWorldPos() + movement);

		mPrevMoveDir = mCurrMoveDir;
	}
	else
	{
		mCurrMoveDir = FVector2D::ZERO;
	}
	mAccumulatedDir = FVector2D::ZERO;
}

void CMovementComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CMovementComponent>(this);
}