#pragma once
#include "Object.h"

class CMonster : public CObject
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	virtual void Release() final;
};