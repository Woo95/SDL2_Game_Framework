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
	virtual bool Init() final;

private:
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

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