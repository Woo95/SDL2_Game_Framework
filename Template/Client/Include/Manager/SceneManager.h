#pragma once

#include "../Core/GameInfo.h"
#include "../Core/SceneState.h"

class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

private:
	std::stack<class CScene*> mScene;

	static CSceneManager* mInst;

public:
	bool Init();
	void Update(float DeltaTime);
	void LateUpdate(float DeltaTime);
	void Render(SDL_Renderer* Renderer);
	void Change(EScene::State ESceneState);

public:
	static CSceneManager* GetInst()
	{
		if (!mInst)
			mInst = new CSceneManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};