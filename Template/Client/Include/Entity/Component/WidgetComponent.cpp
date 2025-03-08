#include "WidgetComponent.h"
#include "../../Widget/WidgetBase.h"
#include "../Object/Object.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Camera.h"

CWidgetComponent::CWidgetComponent() :
	mWidget(nullptr)
{
}

CWidgetComponent::~CWidgetComponent()
{
	if (mWidget)
		mWidget->Release();
}

bool CWidgetComponent::Init()
{
	return CComponent::Init();
}

void CWidgetComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	if (mWidget)
		mWidget->Update(DeltaTime);
}

void CWidgetComponent::LateUpdate(float DeltaTime)
{
	CComponent::LateUpdate(DeltaTime);

	if (mWidget) 
		mWidget->LateUpdate(DeltaTime);
}

void CWidgetComponent::Render(SDL_Renderer* Renderer)
{
	if (mWidget)
	{
		// 월드 스케일, 위치, 피벗을 반환
		const FVector2D& scale = mTransform->GetWorldScale();
		const FVector2D& pos = mTransform->GetWorldPos();
		const FVector2D& pivot = mTransform->GetPivot();

		// 좌상단 좌표 계산
		FVector2D topLeft = pos - pivot * scale;

		// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
		if (CCamera* camera = GetObject()->GetScene()->GetCamera())
			topLeft = camera->GetRenderPos(topLeft);

		// 유저위젯 또는 위젯 그리기
		mWidget->Render(Renderer, topLeft);
	}

	CComponent::Render(Renderer);
}

void CWidgetComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CWidgetComponent>(this);
}

void CWidgetComponent::SetWidget(CWidgetBase* widget)
{
	if (mWidget)
		mWidget->Release();

	mWidget = widget;
}