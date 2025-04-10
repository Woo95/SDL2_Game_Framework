#include "CircleCollider.h"
#include "../../../Manager/CollisionManager.h"
#include "../../Object/Object.h"
#include "../../../Scene/Scene.h"
#include "../../../Scene/Camera.h"

CCircleCollider::CCircleCollider() :
	mCircle({})
{
	mTypeID = typeid(CCircleCollider).hash_code();

	mColliderType = ECollider::Type::CIRCLE;
}

CCircleCollider::~CCircleCollider()
{
}

bool CCircleCollider::Init()
{
	return CCollider::Init();
}

void CCircleCollider::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);

	// 월드 좌표와 스케일 및 피벗 값 가져오기
	FVector2D worldPos = mTransform->GetWorldPos();
	FVector2D pivot    = mTransform->GetPivot();
	FVector2D scale    = mTransform->GetWorldScale();

	// 원 정보 생성
	mCircle.center = worldPos - pivot * scale + scale * 0.5f;
	mCircle.radius = scale.x * 0.5f;
}

void CCircleCollider::LateUpdate(float DeltaTime)
{
    CCollider::LateUpdate(DeltaTime);
}

void CCircleCollider::Render(SDL_Renderer* Renderer)
{
	CCollider::Render(Renderer);

#ifdef _DEBUG	
	// 렌더 색상 설정
	if (!mIsCollided)
		SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 255);
	else
		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

	// 해당 객체의 위치와 크기를 포함한 영역을 반환
	FCircle renderCircle = mCircle;

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	if (CCamera* camera = GetObject()->GetScene()->GetCamera())
		renderCircle.center = camera->GetRenderPos(renderCircle.center);

	// 원 그리기
	RenderDrawCircle(Renderer, renderCircle);
#endif
}

void CCircleCollider::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CCircleCollider>(this);
}

bool CCircleCollider::Intersect(CCollider* other)
{
	switch (other->GetColliderType())
	{
	case ECollider::Type::CIRCLE:
		return CCollisionManager::GetInst()->CircleCircleCollision(this, (CCircleCollider*)other);
	case ECollider::Type::BOX:
		return CCollisionManager::GetInst()->AABBCircleCollision((CBoxCollider*)other, this);
	}
	return true;
}

// Bresenham's circle drawing algorithm
void CCircleCollider::RenderDrawCircle(SDL_Renderer* renderer, const FCircle& circle)
{
    int x  = static_cast<int>(circle.radius);
    int y  = 0;                               
    int dx = 1;                              
    int dy = 1;                              
    int errorTerm = dx - (2 * static_cast<int>(circle.radius)); // 오차값

    // 원을 8방향 대칭으로 그리기
    while (x >= y)
    {
        // 8방향에 대칭되는 점들을 그린다
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) + x, static_cast<int>(circle.center.y) + y);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) + y, static_cast<int>(circle.center.y) + x);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) - y, static_cast<int>(circle.center.y) + x);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) - x, static_cast<int>(circle.center.y) + y);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) - x, static_cast<int>(circle.center.y) - y);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) - y, static_cast<int>(circle.center.y) - x);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) + y, static_cast<int>(circle.center.y) - x);
        SDL_RenderDrawPoint(renderer, static_cast<int>(circle.center.x) + x, static_cast<int>(circle.center.y) - y);

        // x값 증가, 오차값 업데이트
        if (errorTerm <= 0)
        {
            y++;
            errorTerm += dy;
            dy += 2;
        }

        // y값 감소, 오차값 업데이트
        if (errorTerm > 0)
        {
            x--;
            dx += 2;
            errorTerm += dx - (2 * static_cast<int>(circle.radius));
        }
    }
}