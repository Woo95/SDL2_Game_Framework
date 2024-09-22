#include "PlayScene.h"
#include "../Manager/SceneManager.h"
#include "../Entity/Object/Player.h"
#include "../Entity/Object/Monster.h"
#include "../Manager/MemoryPoolManager.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
	Exit();
}

bool CPlayScene::Enter()
{
	CreatePoolAndSync<CMonster>(50);
	AllocateObject<CMonster>("Monster");

	CreateObject<CPlayer>("Player");

	return true;
}

bool CPlayScene::Exit()
{
	DeletePoolAndSync<CMonster>();

	// CSceneManager::GetInst()->Change(EScene::State::RESULT);

	return true;
}