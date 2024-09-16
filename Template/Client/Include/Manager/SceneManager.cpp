#include "SceneManager.h"
#include "../Scene/MenuScene.h"
#include "../Scene/PlayScene.h"
#include "MemoryPoolManager.h"

CSceneManager* CSceneManager::mInst = nullptr;

CSceneManager::CSceneManager()
{
	mScene.push(new CMenuScene);
}

CSceneManager::~CSceneManager()
{
	while (!mScene.empty())
	{
		SAFE_DELETE(mScene.top());
		mScene.pop();
	}
}

bool CSceneManager::Init()
{
	if (mScene.empty() || !mScene.top()->Enter())
		return false;

	return true;
}

void CSceneManager::Update(float DeltaTime)
{
	mScene.top()->Update(DeltaTime);
}

void CSceneManager::Render(SDL_Renderer* Renderer)
{
	mScene.top()->Render(Renderer);
}

void CSceneManager::Change(EScene::State ESceneState)
{
	if (!mScene.empty())
	{
		SAFE_DELETE(mScene.top());
		mScene.pop();
	}

	switch (ESceneState)
	{
	case EScene::MENU:
		// mScene.push(new CMainMenuScene);
		break;
	case EScene::PLAY:
		mScene.push(new CPlayScene);
		break;
	case EScene::RESULT:
		// mScene.push(new CResultScene);
		break;
	default:
		break;
	}

	Init();
}