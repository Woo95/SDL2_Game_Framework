#pragma once

#include "Core/GameInfo.h"
#include "Core/Vector2D.h"

class CEngine
{
	friend class CClient;

private:
	CEngine();
	~CEngine();

private:
	static CEngine* mInst;

	// SDL core
	SDL_Window*   mWindow   = nullptr;
	SDL_Renderer* mRenderer = nullptr;

	// Runtime flag
	bool mLoop = true;

public:
	SDL_Renderer* GetRenderer() const { return mRenderer; }
	FVector2D GetResolution() const
	{
		int w, h;
		SDL_GetWindowSize(mWindow, &w, &h);
		return { float(w), float(h) };
	}

private:
	bool Init();
	void Run();

	void Update();
	void LateUpdate();
	void Render();

public:
	static CEngine* GetInst()
	{
		if (!mInst)
			mInst = new CEngine;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};