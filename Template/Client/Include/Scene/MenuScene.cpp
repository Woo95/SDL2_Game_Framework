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

	CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(5);
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("TitleIntro_SFX")->Play();
	//CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("TitleIntro_SFX")->SetVolume(5);

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

void CMenuScene::LoadResources()
{
	LoadTexture("UI",      "UI.png");
	LoadTexture("IntroBG", "IntroBG.png");

	LoadFont("Cormorant", "Cormorant.ttf", 32);

	LoadSFX("TitleIntro_SFX", "sfx_titleIntro.wav");
}