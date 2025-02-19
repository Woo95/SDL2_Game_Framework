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
	virtual bool Init()                         override;
	virtual void Update(float DeltaTime)        override;
	virtual void LateUpdate(float DeltaTime)    override;
	virtual void Render(SDL_Renderer* Renderer) override;

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