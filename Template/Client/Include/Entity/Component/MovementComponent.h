#pragma once

#include "Component.h"

class CMovementComponent : public CComponent
{
public:
	CMovementComponent();
	virtual ~CMovementComponent();

private:
	FVector2D mMoveDir;
	FVector2D mFacingDir;

	float mSpeed;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime)        final;
	virtual void LateUpdate(float deltaTime)    final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release()                      final;

public:
	const FVector2D& GetFacingDir() const { return mFacingDir; }
	float GetSpeed() const { return mSpeed; }

	void SetSpeed(float speed)
	{
		mSpeed = speed;
	}

	void AddMoveInput(const FVector2D& direction)
	{
		mMoveDir += direction;
	}

private:
	void Move(float deltaTime);
};