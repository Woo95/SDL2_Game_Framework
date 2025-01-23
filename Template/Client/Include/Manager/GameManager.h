#pragma once

#include "../Core/GameInfo.h"

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

