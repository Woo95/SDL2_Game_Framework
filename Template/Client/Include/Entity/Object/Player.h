#pragma once

#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	class CMovementComponent* mMovementComponent;
	class CCollider*          mColliderComponent;
	class CSpriteComponent*   mSpriteComponent;
	class CWidgetComponent*   mWidgetComponent;

public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	virtual void Release() final;

private:
	void SetupInput();

	void MOVE_UP();
	void MOVE_DOWN();
	void MOVE_LEFT();
	void MOVE_RIGHT();

	void KnockBackOpponent(CCollider* self, CCollider* other);

	void SHOOT();
};