#include "Rigidbody.h"
#include "../../Core/PhysicsConfig.h"
#include "../Object/Object.h"

CRigidbody::CRigidbody() :
	mType(ERigidbodyType::DYNAMIC),
	mMass(100.0f),
	mGravityScale(0.0f),
	mVelocity(FVector2D::ZERO),
	mAcceleration(FVector2D::ZERO),
	mAccumulatedForce(FVector2D::ZERO)
{
	mTypeID = typeid(CRigidbody).hash_code();
}

CRigidbody::~CRigidbody()
{
}

void CRigidbody::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	if (mType == ERigidbodyType::STATIC || mMass <= 0.0f)
		return;

	ApplyGravity();

	ApplyForces();
	
	ApplyAcceleration(deltaTime);

	ApplyDrag(deltaTime);

	UpdateObjectPos(deltaTime);

	ClearForces();
}

void CRigidbody::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CRigidbody>(this);
}

// ========== 외부 물리 처리 함수들 ========== //

// 외부에서 힘을 추가 (지속적인)
void CRigidbody::AddForce(const FVector2D& force)
{
	mAccumulatedForce += force;
}

// 외부에서 충격 힘을 추가 (순간적인)
void CRigidbody::AddImpulse(const FVector2D& impulse)
{
	if (mMass > 0.f)
		mVelocity += impulse / mMass;
}

// ========== 내부 물리 처리 함수들 ========== //

// 중력을 힘에 누적
void CRigidbody::ApplyGravity()
{
	mAccumulatedForce += PhysicsConfig::GravityDir * mGravityScale * mMass * PhysicsConfig::PixelsPerMeter;
}

// 누적된 힘으로 가속도 계산
void CRigidbody::ApplyForces()
{
	mAcceleration = mAccumulatedForce / mMass;
}

// 가속도 만큼 속도 증가
void CRigidbody::ApplyAcceleration(float deltaTime)
{
	mVelocity += mAcceleration * deltaTime;
}

// 속도에 공기 저항 적용
void CRigidbody::ApplyDrag(float deltaTime)
{
	mVelocity *= std::exp(-PhysicsConfig::LinearDrag * deltaTime);
}

// 속도에 따라 오브젝트의 상대적 위치를 갱신
void CRigidbody::UpdateObjectPos(float deltaTime)
{
	if (CTransform* transform = mObject->GetTransform())
	{
		// 속도에 의한 이동 계산 후, 로컬 위치 업데이트
		FVector2D newRelativePos = transform->GetRelativePos() + mVelocity * deltaTime;

		// 상대적 위치를 업데이트 (월드 위치는 내부적으로 갱신됨)
		transform->SetRelativePos(newRelativePos);
	}
}

// 누적된 힘 초기화
void CRigidbody::ClearForces()
{
	mAccumulatedForce = FVector2D::ZERO;
}