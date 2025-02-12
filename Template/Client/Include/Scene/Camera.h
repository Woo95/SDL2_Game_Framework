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
	const FVector2D GetWorldPos(const FVector2D& screenPos) const { return screenPos + mLookAt - (mResolution * 0.5f); }
	
	const FVector2D& GetLookAt() const { return mLookAt; };
	const FVector2D& GetResolution() const { return mResolution; }

	void SetLookAt(const FVector2D& lookAt) { mLookAt = lookAt; }
	void SetTarget(CObject* target) { mTarget = target; }
	void SetResolution(const FVector2D& resolution) { mResolution = resolution; }
};