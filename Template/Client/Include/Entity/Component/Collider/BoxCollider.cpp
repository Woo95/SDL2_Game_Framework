#include "BoxCollider.h"
#include "../../../Manager/CollisionManager.h"
#include "../../Object/Object.h"
#include "../../../Scene/Scene.h"
#include "../../../Scene/Camera.h"

CBoxCollider::CBoxCollider() :
	mRect({})
{
	mTypeID = typeid(CBoxCollider).hash_code();

	mColliderType = ECollider::Type::BOX;
}

CBoxCollider::~CBoxCollider()
{
}

bool CBoxCollider::Init()
{
	return CCollider::Init();
}

void CBoxCollider::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);

	// 월드 스케일, 위치, 피벗을 반환
	const FVector2D& scale = mTransform->GetWorldScale();
	const FVector2D& pos   = mTransform->GetWorldPos();
	const FVector2D& pivot = mTransform->GetPivot();

	// 좌상단 좌표 계산
	FVector2D topLeft = pos - pivot * scale;

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
	if (!mCollidedCount)
		SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

	// 해당 객체의 위치와 크기를 포함한 영역을 반환
	SDL_FRect renderRect = mRect;

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	if (CCamera* camera = GetObject()->GetScene()->GetCamera())
		renderRect = camera->GetRenderPos(renderRect);

	// 사각형 그리기
	SDL_RenderDrawRectF(Renderer, &renderRect);
#endif
}

void CBoxCollider::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CBoxCollider>(this);
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