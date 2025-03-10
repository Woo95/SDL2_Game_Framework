#pragma once

#include "../Core/GameInfo.h"
#include "../Core/Vector2D.h"

class CGameManager
{
private:
	CGameManager();
	~CGameManager();

private:
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;
	bool mLoop = true;

	static CGameManager* mInst;

public:
	bool Init();
	int  Run();

public:
	SDL_Renderer* GetRenderer() const { return mRenderer; }
	FVector2D GetResolution() const
	{
		int width, height;
		SDL_GetWindowSize(mWindow, &width, &height);

		return FVector2D(float(width), float(height));
	}

private:
	void Logic();

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

