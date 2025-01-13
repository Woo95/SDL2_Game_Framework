#include "MenuScene.h"
#include "../Manager/SceneManager.h"

CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{
}

bool CMenuScene::Enter()
{
	return Exit();
}

bool CMenuScene::Exit()
{
	CSceneManager::GetInst()->Change(EScene::State::PLAY);

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
