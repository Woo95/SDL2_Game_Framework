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
	virtual bool Init() final;

private:
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

	virtual bool Intersect(CCollider* other)    final;

public:
	const FCircle& GetCircle() const { return mCircle; }

private:
	void RenderDrawCircle(SDL_Renderer* renderer, const FCircle& circle);
};