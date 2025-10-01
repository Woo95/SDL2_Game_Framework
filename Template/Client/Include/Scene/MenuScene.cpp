#include "MenuScene.h"
#include "Extension/MenuUI.h"
#include "../Manager/SceneManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/TextureManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CMenuScene::CMenuScene()
{
	mSceneUI = new CMenuUI;
}

CMenuScene::~CMenuScene()
{
	SAFE_DELETE(mSceneUI);
}

bool CMenuScene::Enter(void* payload)
{
	mSceneUI->Init();

	CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(0.1f);
	CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("TitleIntro_SFX")->Play();
	//CAssetManager::GetInst()->GetSoundManager()->GetSound<CSFX>("TitleIntro_SFX")->SetVolume(0.1f);
	
	// Bind Event Listener
	CEventManager::GetInst()->AddListener(EEventType::GOTO_PLAY_SCENE, [this](void*)
	{
		CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::PLAY);
	});

	return true;
}

bool CMenuScene::Exit()
{
	CEventManager::GetInst()->ClearListener();

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