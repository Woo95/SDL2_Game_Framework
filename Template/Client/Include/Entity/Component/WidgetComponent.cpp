#include "WidgetComponent.h"
#include "../Object/Object.h"
#include "../../Widget/Widget.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Extension/Camera.h"

CWidgetComponent::CWidgetComponent() :
	mWidget(nullptr)
{
	mTypeID = typeid(CWidgetComponent).hash_code();
}

CWidgetComponent::~CWidgetComponent()
{
	if (mWidget)
		mWidget->Release();
}

void CWidgetComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	if (mWidget)
		mWidget->Update(deltaTime);
}

void CWidgetComponent::LateUpdate(float deltaTime)
{
	CComponent::LateUpdate(deltaTime);

	if (mWidget) 
		mWidget->LateUpdate(deltaTime);
}

void CWidgetComponent::Render(SDL_Renderer* renderer)
{
	if (mWidget && IsVisibleToCamera())
		mWidget->Render(renderer, GetCameraSpaceTopLeft());

	CComponent::Render(renderer);
}

void CWidgetComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CWidgetComponent>(this);
}

void CWidgetComponent::SetWidget(CWidget* widget)
{
	if (mWidget)
		mWidget->Release();

	mWidget = widget;
}

SDL_Rect CWidgetComponent::GetWidgetDest() const
{
	// 부모인 컴포넌트의 월드 위치
	const FVector2D& componentPos = mTransform->GetWorldPos();

	// 위젯 자체의 월드 스케일, 상대 위치, 피벗 정보
	const FVector2D& widgetScale = mWidget->GetTransform()->GetWorldScale();
	const FVector2D& widgetPos   = mWidget->GetTransform()->GetRelativePos();
	const FVector2D& widgetPivot = mWidget->GetTransform()->GetPivot();

	// 좌상단 좌표 계산
	FVector2D topLeft = componentPos + widgetPos - widgetPivot * widgetScale;

	// 사각형 정보 생성
	return { (int)topLeft.x, (int)topLeft.y, (int)widgetScale.x, (int)widgetScale.y };
}

bool CWidgetComponent::IsVisibleToCamera() const
{
	if (CCamera* camera = mObject->GetScene()->GetCamera())
	{
		SDL_Rect widgetRect = GetWidgetDest();
		SDL_Rect cameraRect = camera->GetViewRect();

		if (!SDL_HasIntersection(&widgetRect, &cameraRect))
			return false;
	}
	return true;
}

FVector2D CWidgetComponent::GetCameraSpaceTopLeft() const
{
	// 월드 스케일, 위치, 피벗을 반환
	const FVector2D& scale = mTransform->GetWorldScale();
	const FVector2D& pos   = mTransform->GetWorldPos();
	const FVector2D& pivot = mTransform->GetPivot();

	// 좌상단 좌표 계산
	FVector2D topLeft = pos - pivot * scale;

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	if (CCamera* camera = mObject->GetScene()->GetCamera())
		topLeft = camera->GetRenderPos(topLeft);

	return topLeft;
}