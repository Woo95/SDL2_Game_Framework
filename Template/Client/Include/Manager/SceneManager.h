#pragma once

#include "../Core/GameInfo.h"
#include "../Core/Utils/SceneUtils.h"

class CScene;

class CSceneManager
{
	friend class CGameManager;

private:
	CSceneManager();
	~CSceneManager();

private:
	std::stack<CScene*> mScene;
	EScene::State mPendingScene = EScene::State::NONE;

	static CSceneManager* mInst;

public:
	CScene* GetCurrentScene() const { return mScene.top(); }

	void PendingChange(EScene::State state);
	void ApplyChange(EScene::State state);

private:
	bool Init();
	void Update(float deltaTime);
	void LateUpdate(float deltaTime);
	void Render(SDL_Renderer* renderer);

	CScene* GetSceneFromState(EScene::State state);
	
public:
	static CSceneManager* GetInst()
	{
		if (!mInst)
			mInst = new CSceneManager;
		return mInst;
	}
private:
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};