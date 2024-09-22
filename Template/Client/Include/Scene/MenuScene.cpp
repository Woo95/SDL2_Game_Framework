#include "MenuScene.h"
#include "../Manager/SceneManager.h"

CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{
}

bool CMenuScene::Enter()
{
	if (!Exit())
		return false;

	return true;
}

bool CMenuScene::Exit()
{
	CSceneManager::GetInst()->Change(EScene::State::PLAY);

	return true;
}