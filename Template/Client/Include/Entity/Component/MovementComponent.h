#pragma once

#include "Component.h"

class CMovementComponent : public CComponent
{
public:
	CMovementComponent();
	virtual ~CMovementComponent();

private:
	float mSpeed;

	FVector2D mAccumulatedDir;
	FVector2D mPrevMoveDir;
	FVector2D mCurrMoveDir;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	void AddMoveDir(const FVector2D& direction)
	{
		mAccumulatedDir += direction;
	}

	const FVector2D& GetPrevMoveDir() const { return mPrevMoveDir; }
	const FVector2D& GetCurrMoveDir() const { return mCurrMoveDir; }

	float GetSpeed() const { return mSpeed; }
	void SetSpeed(float speed)
	{
		mSpeed = speed;
	}
};