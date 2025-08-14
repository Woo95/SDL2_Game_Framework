#pragma once
#include "Object.h"

class CCollider;
class CVFXComponent;

class CMonster : public CObject
{
public:
	CMonster();
	virtual ~CMonster();

private:
	CCollider* mCollider;
	CVFXComponent* mVFX;

public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	virtual void Release() final;

public:
	void OnHit(CCollider* self, CCollider* other);
};