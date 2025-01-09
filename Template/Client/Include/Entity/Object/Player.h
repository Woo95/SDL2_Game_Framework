#pragma once

#include "Object.h"
#include "../../Core/Timer.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	class CMovementComponent* mMovementComponent;
	class CCollider* mCollider;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual void Release() final;

private:
	void SetupInput();

	void MOVE_UP();
	void MOVE_DOWN();
	void MOVE_LEFT();
	void MOVE_RIGHT();

	void SHOOT();
};