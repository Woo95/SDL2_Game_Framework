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

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	void AddMoveDir(const FVector2D& direction)
	{
		mAccumulatedDir += direction;
	}

	const FVector2D& GetMoveDir() const { return mPrevMoveDir; }

	float GetSpeed() const { return mSpeed; }
	void SetSpeed(float speed)
	{
		mSpeed = speed;
	}
};