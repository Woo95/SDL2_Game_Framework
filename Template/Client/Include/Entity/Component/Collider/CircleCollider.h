#pragma once

#include "Collider.h"

struct FCircle
{
	FVector2D center;
	float	  radius;
};

class CCircleCollider : public CCollider
{
public:
	CCircleCollider();
	virtual ~CCircleCollider();

private:
	FCircle mCircle;

public:
	virtual bool Init()                         override;
	virtual void Update(float DeltaTime)        override;
	virtual void LateUpdate(float DeltaTime)    override;
	virtual void Render(SDL_Renderer* Renderer) override;

	virtual bool Intersect(CCollider* other) final;

private:
	virtual void Release() final;

public:
	const FCircle& GetCircle() const { return mCircle; }

private:
	void RenderDrawCircle(SDL_Renderer* renderer, const FCircle& circle);
};