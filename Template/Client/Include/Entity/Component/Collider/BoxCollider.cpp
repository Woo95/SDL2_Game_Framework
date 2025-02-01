#include "BoxCollider.h"
#include "../../../Manager/CollisionManager.h"
#include "../../Object/Object.h"
#include "../../../Scene/Scene.h"
#include "../../../Scene/Camera.h"

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

void CBoxCollider::LateUpdate(float DeltaTime)
{
	CCollider::LateUpdate(DeltaTime);
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

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	CCamera* camera = GetObject()->GetScene()->GetCamera();
	if (camera)
	{
		const FVector2D renderPos = camera->GetRenderPos(FVector2D(mRect.x, mRect.y));

		mRect = { renderPos.x, renderPos.y, mRect.w, mRect.h };
	}

	// 사각형 그리기
	SDL_RenderDrawRectF(Renderer, &mRect);
#endif
}

bool CBoxCollider::Intersect(CCollider* other)
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

void CBoxCollider::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBoxCollider>(this);
}