#pragma once

#include "GameInfo.h"

class CGameManager
{
private:
	SDL_Window* mWindow = nullptr;
	SDL_Renderer* mRenderer = nullptr;
	bool mLoop = true;

private:
	CGameManager();
	~CGameManager();

public:
	bool Init();
	int Run();

private:
	void Logic();
	void Update();
	void Render();

private:
	static CGameManager* mInst;

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

