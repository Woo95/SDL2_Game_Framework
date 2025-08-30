#pragma once

#include "../../Core/GameInfo.h"
#include "../../Core/Vector2D.h"

class CObject;

class CCamera
{
	friend class CScene;

public:
	CCamera();
	~CCamera();

private:
	FVector2D mLookAt; // 카메라가 보는 위치
	CObject*  mTarget;

	FVector2D mResolution;

protected:
	void Update(float deltaTime);

public:
	const FVector2D GetRenderPos(const FVector2D& objPos) const { return objPos - mLookAt + (mResolution * 0.5f); }
	const SDL_FRect GetRenderPos(const SDL_FRect& objFRect) const
	{
		return SDL_FRect
		{
			objFRect.x - mLookAt.x + (mResolution.x * 0.5f),
			objFRect.y - mLookAt.y + (mResolution.y * 0.5f),
			objFRect.w,
			objFRect.h
		};
	}
	const FVector2D GetWorldPos(const FVector2D& screenPos) const { return screenPos + mLookAt - (mResolution * 0.5f); }

	const SDL_Rect GetViewRect() const
	{
		FVector2D halfSize = mResolution * 0.5f;
		FVector2D topLeft = mLookAt - halfSize;

		return SDL_Rect
		{
			(int)(topLeft.x),
			(int)(topLeft.y),
			(int)(mResolution.x),
			(int)(mResolution.y)
		};
	}

	const FVector2D& GetLookAt() const { return mLookAt; };
	const FVector2D& GetResolution() const { return mResolution; }

	void SetTarget(CObject* target) { mTarget = target; }
	void SetResolution(const FVector2D& resolution) { mResolution = resolution; }
};