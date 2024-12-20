#pragma once

#include "Collider.h"

struct FCircle
{
	FVector2D mCenter;
	float	  mRadius;
};

class CCircleCollider : public CCollider
{
public:
	CCircleCollider();
	virtual ~CCircleCollider() = default;

private:
	FCircle mCircle;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual bool Release() final;

	virtual bool Collision(CCollider* other)        final;
	virtual void OnCollisionEnter(CCollider* other) final;
	virtual void OnCollisionStay(CCollider* other)  final;
	virtual void OnCollisionExit(CCollider* other)  final;

public:
	const FCircle& GetCircle() const { return mCircle; }

private:
	void RenderDrawCircle(SDL_Renderer* renderer, const FCircle& circle);
};