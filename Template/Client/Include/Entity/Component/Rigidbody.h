#pragma once

#include "Component.h"
#include "../../Core/Utils/PhysicsUtils.h"

class CRigidbody : public CComponent
{
public:
	CRigidbody();
	virtual ~CRigidbody();

private:
	ERigidbodyType mType;

	float mMass;
	float mGravityScale;

	FVector2D mVelocity;
	FVector2D mAcceleration;
	FVector2D mAccumulatedForce;

private:
	virtual void Update(float deltaTime) final;
	virtual void Release() final;

public:
	void AddForce(const FVector2D& force);
	void AddImpulse(const FVector2D& impulse);

	const FVector2D& GetVelocity() const { return mVelocity; }
	ERigidbodyType GetType() const { return mType; }
	float GetMass() const { return mMass; }

	void SetVelocity(const FVector2D& velocity)
	{
		mVelocity = velocity;
	}
	void SetType(ERigidbodyType type)
	{
		mType = type;
	}
	void SetMass(float mass)
	{
		mMass = mass;
	}
	void SetGravityScale(float scale)
	{
		mGravityScale = scale;
	}

private:
	void ApplyGravity();
	void ApplyForces();
	void ApplyAcceleration(float deltaTime);
	void ApplyDrag(float deltaTime);
	void UpdateObjectPos(float deltaTime);
	void ClearForces();
};