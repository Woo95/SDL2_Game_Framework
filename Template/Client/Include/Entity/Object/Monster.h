#pragma once
#include "Object.h"

class CMonster : public CObject
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() final;
};