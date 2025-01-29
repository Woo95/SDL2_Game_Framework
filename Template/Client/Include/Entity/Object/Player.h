#pragma once

#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	class CMovementComponent* mMovementComponent;
	class CCollider* mColliderComponent;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual void Release() final;

private:
	void SetupInput();

	void MOVE_UP();
	void MOVE_DOWN();
	void MOVE_LEFT();
	void MOVE_RIGHT();

	void SHOOT();
};