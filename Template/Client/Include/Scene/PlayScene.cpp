#include "PlayScene.h"
#include "../Manager/SceneManager.h"
#include "../Entity/Object/Player.h"
#include "../Entity/Object/Monster.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
	Exit();
}

bool CPlayScene::Enter()
{
	AllocateObject<CMonster, 10>("Monster");

	CreateObject<CPlayer>("Player");

	return true;
}

bool CPlayScene::Exit()
{
	// CSceneManager::GetInst()->Change(EScene::State::RESULT);

	return true;
}