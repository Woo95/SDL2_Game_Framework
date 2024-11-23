#pragma once
#include "Object.h"

class CBullet : public CObject
{
public:
	CBullet();
	virtual ~CBullet() = default;

public:
	class CMovementComponent* mMovementComponent;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual bool Release() final;
};