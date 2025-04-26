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
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	virtual void Release() final;
};