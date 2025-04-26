#pragma once

#include "Object.h"

class CBackground : public CObject
{
public:
	CBackground();
	virtual ~CBackground();

public:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	virtual void Release() final;

};

