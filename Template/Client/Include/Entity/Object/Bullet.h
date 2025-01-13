#pragma once
#include "Object.h"

class CBullet : public CObject
{
public:
	CBullet();
	virtual ~CBullet();

public:
	class CMovementComponent* mMovementComponent;
	class CCollider* mCollider;

	float mDestroyTime;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual void Release() final;
};