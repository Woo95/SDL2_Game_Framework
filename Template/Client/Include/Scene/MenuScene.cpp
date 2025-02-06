#include "MenuScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"

CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{
}

bool CMenuScene::Enter()
{
	CSceneManager::GetInst()->Change(EScene::State::PLAY);

	return true;
}

bool CMenuScene::Exit()
{
	return true;
}

void CMenuScene::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
}

void CMenuScene::LateUpdate(float DeltaTime)
{
	CScene::LateUpdate(DeltaTime);
}

void CMenuScene::Render(SDL_Renderer* Renderer)
{
	CScene::Render(Renderer);
}

void CMenuScene::LoadTextures()
{
	CTextureManager* TM = CAssetManager::GetInst()->GetTextureManager();

	TM->LoadTexture("Antonio",    "Antonio.png",                this);
	TM->LoadTexture("Imelda",     "Imelda.png",                 this);
	TM->LoadTexture("Pasqualina", "Pasqualina.png",             this);
	TM->LoadTexture("Stage2",     "Inlaid_Library_stage_2.png", this);
}