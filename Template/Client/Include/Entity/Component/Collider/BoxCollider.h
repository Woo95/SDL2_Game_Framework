#pragma once

#include "Collider.h"

class CBoxCollider : public CCollider
{
public:
	CBoxCollider();
	virtual ~CBoxCollider();

private:
	SDL_FRect mRect;

public:
	virtual bool Init() final;

private:
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

	virtual bool Intersect(CCollider* other)    final;

public:
	const SDL_FRect& GetRect() const { return mRect; }
};