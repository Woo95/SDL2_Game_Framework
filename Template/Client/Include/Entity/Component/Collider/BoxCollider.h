#pragma once

#include "Collider.h"

class CBoxCollider : public CCollider
{
public:
	CBoxCollider();
	virtual ~CBoxCollider();

private:
	SDL_FRect mRect;

private:
	virtual void Update(float deltaTime)        final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release()                      final;

	virtual bool Intersect(CCollider* other)    final;

public:
	const SDL_FRect& GetRect() const { return mRect; }
};