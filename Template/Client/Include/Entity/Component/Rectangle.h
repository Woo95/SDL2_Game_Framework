#pragma once

#include "Component.h"

struct RGB
{
	Uint8 R = 255; 
	Uint8 G = 255;
	Uint8 B = 255;
};

class CRectangle : public CComponent
{
public:
	CRectangle() = default;
	virtual ~CRectangle();

public:
	RGB mRGB;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() final;	// Object.h에서 component memoryPool usage 위하여

public:
	void SetColor(Uint8 r, Uint8 g, Uint8 b)
	{
		mRGB.R = r;
		mRGB.G = g;
		mRGB.B = b;
	}
};