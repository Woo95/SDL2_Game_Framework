#pragma once

#include "../Core/GameInfo.h"
#include "../Core/Vector2D.h"

class CGameManager
{
	friend class CClient;

private:
	CGameManager();
	~CGameManager();

private:
	static CGameManager* mInst;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mLoop;

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
	static CGameManager* GetInst()
	{
		if (!mInst)
			mInst = new CGameManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};