#pragma once
#include "Component.h"
#include "../../Core/Vector2D.h"

class CMovementComponent : public CComponent
{
public:
	CMovementComponent();
	virtual ~CMovementComponent() = default;

private:
	float mSpeed;
	FVector2D mDirection;

public:
	virtual void Update(float DeltaTime);

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