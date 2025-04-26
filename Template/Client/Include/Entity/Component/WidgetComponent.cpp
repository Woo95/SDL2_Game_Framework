#include "WidgetComponent.h"
#include "../../Widget/Widget.h"
#include "../Object/Object.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Camera.h"

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

bool CWidgetComponent::Init()
{
	return CComponent::Init();
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

		// 위젯 그리기
		mWidget->Render(renderer, topLeft);
	}

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