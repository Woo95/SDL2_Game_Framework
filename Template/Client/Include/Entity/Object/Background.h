#pragma once

#include "Object.h"

class CBackground : public CObject
{
public:
	CBackground();
	virtual ~CBackground();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual void Release() final;

};

