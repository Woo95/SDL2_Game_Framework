#pragma once
#include "Object.h"

class CBullet : public CObject
{
public:
	CBullet();
	virtual ~CBullet();

public:
	class CMovementComponent* mMovementComponent;

	float mDestroyTime;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual void Release() final;
};