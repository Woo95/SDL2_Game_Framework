#pragma once

#include "../Core/Vector2D.h"

class CObject;

class CCamera
{
	friend class CScene;

public:
	CCamera();
	~CCamera();

private:
	FVector2D   mLookAt; // 카메라가 보는 위치
	CObject*    mTarget;

	FVector2D   mResolution;

protected:
	void Update(float DeltaTime);

public:
	const FVector2D GetRenderPos(const FVector2D& objPos) const { return objPos - mLookAt + (mResolution * 0.5f); }

	void SetLookAt(const FVector2D& lookAt) { mLookAt = lookAt; }
	void SetTarget(CObject* target) { mTarget = target; }
	void SetResolution(const FVector2D& resolution) { mResolution = resolution; }
};