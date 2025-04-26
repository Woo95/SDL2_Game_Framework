#include "MenuScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Manager/Resource/SoundManager.h"
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

	CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(0.1f);
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("TitleIntro_SFX")->Play();
	//CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("TitleIntro_SFX")->SetVolume(0.1f);

	return true;
}

bool CMenuScene::Exit()
{
	return true;
}

void CMenuScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);
}

void CMenuScene::LateUpdate(float deltaTime)
{
	CScene::LateUpdate(deltaTime);
}

void CMenuScene::Render(SDL_Renderer* renderer)
{
	CScene::Render(renderer);
}

void CMenuScene::LoadResources()
{
	LoadTexture("UI",      "UI.png");
	LoadTexture("IntroBG", "IntroBG.png");

	LoadFont("Cormorant", "Cormorant.ttf", 32);

	LoadSFX("TitleIntro_SFX", "sfx_titleIntro.wav");
}