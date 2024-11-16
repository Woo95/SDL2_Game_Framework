#pragma once

#include "Component.h"

class CRectangle : public CComponent
{
public:
	CRectangle() = default;
	virtual ~CRectangle();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() final;	// Object.h에서 component memoryPool usage 위하여
};