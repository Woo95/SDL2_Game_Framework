#include "BoxCollider.h"
#include "../../Manager/CollisionManager.h"

CBoxCollider::CBoxCollider() :
	mRect{}
{
	mColliderType = ECollider::Type::BOX;
}

CBoxCollider::~CBoxCollider()
{
}

bool CBoxCollider::Init()
{
	CCollider::Init();

	SetProfile("TestProfile");

	return true;
}

void CBoxCollider::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);

	// 월드 좌표와 스케일을 사용해 좌상단 좌표 계산
	const FVector2D& scale   = mTransform->GetWorldScale();
	const FVector2D& topLeft = mTransform->GetWorldPos() - mTransform->GetPivot() * scale;

	// 사각형 정보 생성
	mRect = { topLeft.x, topLeft.y, scale.x, scale.y };
}

void CBoxCollider::Render(SDL_Renderer* Renderer)
{
	CCollider::Render(Renderer);

#ifdef _DEBUG	
	// 렌더 색상 설정
	if (!mIsCollided)
		SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

	// 사각형 그리기
	SDL_RenderDrawRectF(Renderer, &mRect);
#endif
}

bool CBoxCollider::Release()
{
	if (CMemoryPoolManager::GetInst()->HasPool<CBoxCollider>())
	{
		CMemoryPoolManager::GetInst()->Deallocate<CBoxCollider>(this);
		return true;
	}
	return false;
}

bool CBoxCollider::Collision(CCollider* other)
{
	switch (other->GetColliderType())
	{
	case ECollider::Type::BOX:
		return CCollisionManager::GetInst()->AABBCollision(this, (CBoxCollider*)other);
	case ECollider::Type::CIRCLE:
		return CCollisionManager::GetInst()->AABBCircleCollision(this, (CCircleCollider*)other);
	}
	return true;
}

void CBoxCollider::OnCollisionEnter(CCollider* other)
{
	mIsCollided = true;
}

void CBoxCollider::OnCollisionStay(CCollider* other)
{
	mIsCollided = true;
}

void CBoxCollider::OnCollisionExit(CCollider* other)
{
	mIsCollided = false;
}