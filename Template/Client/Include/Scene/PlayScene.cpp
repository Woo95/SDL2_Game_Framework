#include "PlayScene.h"
#include "../Manager/SceneManager.h"
#include "../Entity/Object/Player.h"
#include "../Entity/Object/Monster.h"
#include "../Entity/Object/Background.h"
#include "Collision/SceneCollision.h"
#include "../Scene/Camera.h"

CPlayScene::CPlayScene()
{
	mSceneCollision = new CSceneCollision(mCamera);
}

CPlayScene::~CPlayScene()
{
	SAFE_DELETE(mSceneCollision);

	Exit();
}

bool CPlayScene::Enter()
{
	AllocateObject<CBackground, 1>("Background", ELayer::Type::BACKGROUND);

	CObject* player = AllocateObject<CPlayer, 1>("Player", ELayer::Type::OBJECT);

	AllocateObject<CMonster, 10>("Monster", ELayer::Type::OBJECT);

	mCamera->SetTarget(player);

	return true;
}

bool CPlayScene::Exit()
{
	// CSceneManager::GetInst()->Change(EScene::State::RESULT);

	return true;
}

void CPlayScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
}

void CPlayScene::LateUpdate(float DeltaTime)
{
	CScene::LateUpdate(DeltaTime);
}

void CPlayScene::Render(SDL_Renderer* Renderer)
{
	CScene::Render(Renderer);
}

void CPlayScene::LoadResources()
{
	LoadTexture("UI", "UI.png");

	LoadTexture("Antonio",    "Antonio.png");
	LoadTexture("Imelda",     "Imelda.png");
	LoadTexture("Pasqualina", "Pasqualina.png");
	LoadTexture("Bullet",     "Bullet.png");
	LoadTexture("Stage1",     "Mad_Forest_stage_1.png");
}