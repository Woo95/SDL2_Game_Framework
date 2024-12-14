#pragma once

#include "Collider.h"

class CBoxCollider : public CCollider
{
public:
	CBoxCollider();
	virtual ~CBoxCollider() = default;

private:
	SDL_FRect mRect;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual bool Release() final;

	virtual bool Collision(CCollider* other)        final;
	virtual void OnCollisionBegin(CCollider* other) final;
	virtual void OnCollisionEnd(CCollider* other)   final;

public:
	const SDL_FRect& GetRect() const { return mRect; }
};