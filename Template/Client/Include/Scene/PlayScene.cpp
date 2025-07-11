#include "PlayScene.h"
#include "../Manager/GameManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"
#include "../Scene/Camera.h"
#include "Collision/SceneCollision.h"
#include "../Entity/Object/Player.h"
#include "../Entity/Object/Monster.h"
#include "../Entity/Object/Background.h"

CPlayScene::CPlayScene()
{
	mCamera = new CCamera;
	mCamera->SetResolution(CGameManager::GetInst()->GetResolution());

	mSceneCollision = new CSceneCollision(mCamera);
}

CPlayScene::~CPlayScene()
{
	SAFE_DELETE(mSceneCollision);

	SAFE_DELETE(mCamera);
}

bool CPlayScene::Enter()
{
	InstantiateObject<CBackground, 1>("Background", ELayer::Type::BACKGROUND);

	CObject* player = InstantiateObject<CPlayer, 1>("Player", ELayer::Type::OBJECT);

	InstantiateObject<CMonster, 10>("Monster", ELayer::Type::OBJECT);

	mCamera->SetTarget(player);

	CAssetManager::GetInst()->GetSoundManager()->SetVolume<CBGM>(0.1f);
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CBGM>("Stage1_BGM")->Play();
	//CAssetManager::GetInst()->GetSoundManager()->GetSound<CBGM>("Stage1_BGM")->SetVolume(0.1f);

	return true;
}

bool CPlayScene::Exit()
{
	return true;
}

void CPlayScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);
}

void CPlayScene::LateUpdate(float deltaTime)
{
	CScene::LateUpdate(deltaTime);
}

void CPlayScene::Render(SDL_Renderer* renderer)
{
	CScene::Render(renderer);
}

void CPlayScene::LoadResources()
{
	LoadTexture("UI", "UI.png");

	LoadTexture("Antonio",    "Antonio.png");
	LoadTexture("Imelda",     "Imelda.png");
	LoadTexture("Pasqualina", "Pasqualina.png");
	LoadTexture("Bullet",     "Bullet.png");
	LoadTexture("Stage1",     "Mad_Forest_stage_1.png");

	LoadBGM("Stage1_BGM", "bgm_will_beginning.wav");
}