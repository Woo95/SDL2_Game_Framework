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
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

	virtual bool Intersect(CCollider* other) final;

private:
	virtual void Release() final;

public:
	const SDL_FRect& GetRect() const { return mRect; }
};