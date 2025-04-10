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

public:
	virtual bool Init() final;

private:
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

public:
	void AddForce(const FVector2D& force);
	void AddImpulse(const FVector2D& impulse);

	void SetVelocity(const FVector2D& velocity)
	{
		mVelocity = velocity;
	}
	const FVector2D& GetVelocity() const { return mVelocity; }

	void SetType(ERigidbodyType type)
	{
		mType = type;
	}
	ERigidbodyType GetType() const { return mType; }

	void SetMass(float mass)
	{ 
		mMass = mass;
	}
	float GetMass() const { return mMass; }

private:
	void ApplyGravity();
	void ApplyForces();
	void ApplyAcceleration(float DeltaTime);
	void ApplyDrag(float DeltaTime);
	void UpdateObjectPos(float DeltaTime);
	void ClearForces();
};