#include "PlayScene.h"
#include "../Manager/SceneManager.h"
#include "../Object/Player.h"

CPlayScene::CPlayScene()
{
}

CPlayScene::~CPlayScene()
{
}

bool CPlayScene::Enter()
{
	CPlayer* player = CreateObject<CPlayer>("PlayerA", ObjectType::CHARACTER_A);

	return true;
}

bool CPlayScene::Exit()
{
	CSceneManager::GetInst()->Change(EScene::State::RESULT);

	return true;
}