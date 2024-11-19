#include "Rectangle.h"

CRectangle::~CRectangle()
{
}

bool CRectangle::Init()
{
    return CComponent::Init();
}

void CRectangle::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);
}

void CRectangle::Render(SDL_Renderer* Renderer)
{
    // 부모 클래스 렌더 함수 호출
    CComponent::Render(Renderer);


    const CTransform* transform = GetTransform();
    // 월드 좌표와 스케일을 사용해 좌상단 좌표 계산
    const FVector2D scale = transform->GetWorldScale();
    const FVector2D topLeft = transform->GetWorldPos() - transform->GetPivot() * scale;

    // 사각형 정보 생성
    SDL_FRect rectangle = { topLeft.mX, topLeft.mY, scale.mX, scale.mY };

    // 렌더 색상 설정 (흰색)
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

    // 사각형 그리기
    SDL_RenderDrawRectF(Renderer, &rectangle);
}

bool CRectangle::Release()
{
    if (CMemoryPoolManager::GetInst()->HasPool<CRectangle>())
    {
        CMemoryPoolManager::GetInst()->Deallocate<CRectangle>(this);
        return true;
    }
    return false;
}
