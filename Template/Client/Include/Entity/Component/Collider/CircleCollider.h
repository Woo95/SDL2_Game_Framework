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

private:
	virtual void Update(float deltaTime)        final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release()                      final;

	virtual bool Intersect(CCollider* other)    final;

public:
	const FCircle& GetCircle() const { return mCircle; }

private:
	void RenderDrawCircle(SDL_Renderer* renderer, const FCircle& circle);
};