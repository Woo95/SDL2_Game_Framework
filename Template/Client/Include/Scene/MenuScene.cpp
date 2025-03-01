#include "MenuScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Scene/UI/MenuUI.h"

CMenuScene::CMenuScene()
{
	mSceneUI = new CMenuUI;
}

CMenuScene::~CMenuScene()
{
	SAFE_DELETE(mSceneUI);
}

bool CMenuScene::Enter()
{
	mSceneUI->Init();

	//CSceneManager::GetInst()->Change(EScene::State::PLAY);

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

	TM->LoadTexture("UI", "UI.png", this);
}