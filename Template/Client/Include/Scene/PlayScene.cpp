#include "PlayScene.h"
#include "../Manager/SceneManager.h"
#include "../Entity/Object/Player.h"
#include "../Entity/Object/Monster.h"
#include "Collision/SceneCollision.h"

CPlayScene::CPlayScene()
{
	mSceneCollision = new CSceneCollision(1280, 720); // temporary collision area size
}

CPlayScene::~CPlayScene()
{
	SAFE_DELETE(mSceneCollision);

	Exit();
}

bool CPlayScene::Enter()
{
	//AllocateObject<CMonster, 10>("Monster");

	CreateObject<CPlayer>("Player");

	return true;
}

void CPlayScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
}

void CPlayScene::Render(SDL_Renderer* Renderer)
{
	CScene::Render(Renderer);
}

bool CPlayScene::Exit()
{
	// CSceneManager::GetInst()->Change(EScene::State::RESULT);

	return true;
}