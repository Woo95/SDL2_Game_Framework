#pragma once

#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() final;
};