#pragma once
#include "Object.h"

class CCollider;

class CMonster : public CObject
{
public:
	CMonster();
	virtual ~CMonster();

private:
	CCollider* mCollider;

public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	virtual void Release() final;
};