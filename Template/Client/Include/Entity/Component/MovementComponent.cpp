#include "MovementComponent.h"
#include "../../Entity/Object/Object.h"

CMovementComponent::CMovementComponent() :
	mSpeed(500.f), 
	mDirection(FVector2D::ZERO)
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
	if (mDirection != FVector2D::ZERO)
	{
		CTransform* transform = mObject->GetTransform();

		FVector2D movement = mDirection.GetNormalize() * mSpeed * DeltaTime;

		transform->SetWorldPos(transform->GetWorldPos() + movement);

		mDirection = FVector2D::ZERO;
	}
}