#include "PlayScene.h"
#include "../Manager/SceneManager.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

bool CPlayScene::Enter()
{
	return true;
}

bool CPlayScene::Exit()
{
	CSceneManager::GetInst()->Change(EScene::State::RESULT);

	return true;
}