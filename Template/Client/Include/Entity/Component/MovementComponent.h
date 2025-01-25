#pragma once

#include "Component.h"

class CMovementComponent : public CComponent
{
public:
	CMovementComponent();
	virtual ~CMovementComponent();

private:
	float mSpeed;
	FVector2D mDirection;

public:
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);

private:
	virtual void Release() final;

public:
	float GetSpeed() const
	{ 
		return mSpeed; 
	}
	void SetSpeed(float speed)
	{
		mSpeed = speed;
	}

public:
	void MoveDir(const FVector2D& direction)
	{
		mDirection += direction;
	}

private:
	void Move(float DeltaTime);
};