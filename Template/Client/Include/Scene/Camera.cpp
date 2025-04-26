#include "Camera.h"
#include "../Entity/Object/Object.h"

CCamera::CCamera() :
	mLookAt(FVector2D::ZERO),
	mTarget(nullptr),
	mResolution(FVector2D::ZERO)
{
}

CCamera::~CCamera()
{
}

void CCamera::Update(float deltaTime)
{
	if (!mTarget || !mTarget->GetActive() || !mTarget->GetEnable())
	{
		mTarget = nullptr;
		return;
	}
	mLookAt = mTarget->GetTransform()->GetWorldPos();
}