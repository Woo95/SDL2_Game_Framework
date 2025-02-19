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
	virtual bool Init()                         override;
	virtual void Update(float DeltaTime)        override;
	virtual void LateUpdate(float DeltaTime)    override;
	virtual void Render(SDL_Renderer* Renderer) override;

	virtual bool Intersect(CCollider* other) final;

private:
	virtual void Release() final;

public:
	const SDL_FRect& GetRect() const { return mRect; }
};