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
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual void Release() final;

	virtual bool Collision(CCollider* other)        final;
	virtual void OnCollisionEnter(CCollider* other) final;
	virtual void OnCollisionStay(CCollider* other)  final;
	virtual void OnCollisionExit(CCollider* other)  final;

public:
	const SDL_FRect& GetRect() const { return mRect; }
};