#include "SceneManager.h"
#include "../Scene/MenuScene.h"
#include "../Scene/PlayScene.h"
#include "MemoryPoolManager.h"
#include "../Core/Transform.h"

CSceneManager* CSceneManager::mInst = nullptr;

CSceneManager::CSceneManager()
{
	CMemoryPoolManager::GetInst()->CreatePool<CTransform>(300);

	CMemoryPoolManager::GetInst()->CreatePool<CLayer>(ELayer::Type::MAX);
}

CSceneManager::~CSceneManager()
{
	while (!mScene.empty())
	{
		SAFE_DELETE(mScene.top());
		mScene.pop();
	}

	CMemoryPoolManager::GetInst()->DeletePool<CLayer>();

	CMemoryPoolManager::GetInst()->DeletePool<CTransform>();
}

bool CSceneManager::Init()
{
	Change(EScene::State::MENU);

	return true;
}

void CSceneManager::Update(float DeltaTime)
{
	mScene.top()->Update(DeltaTime);
}

void CSceneManager::LateUpdate(float DeltaTime)
{
	mScene.top()->LateUpdate(DeltaTime);
}

void CSceneManager::Render(SDL_Renderer* Renderer)
{
	mScene.top()->Render(Renderer);
}

void CSceneManager::Change(EScene::State state)
{
	// 새로운 씬 생성 및 텍스쳐 로드
	CScene* newScene = GetSceneFromState(state);
	newScene->LoadTextures();

	// 이전 씬 정리 및 텍스쳐 언로드
	if (!mScene.empty())
	{
		CScene* oldScene = mScene.top();

		// 새로운 씬에서 로드된 텍스쳐 키를 이전 씬에서 삭제
		for (const std::string& key : newScene->mTextureKeys)
			oldScene->mTextureKeys.erase(key);

		oldScene->UnloadTextures();

		if (oldScene->Exit())
		{
			SAFE_DELETE(oldScene);
			mScene.pop();
		}
	}

	// 새로운 씬 추가
	mScene.push(newScene);
	mScene.top()->Enter();
}

CScene* CSceneManager::GetSceneFromState(EScene::State state)
{
	CScene* newScene = nullptr;

	switch (state)
	{
	case EScene::MENU:
		newScene = new CMenuScene;
		break;
	case EScene::PLAY:
		newScene = new CPlayScene;
		break;
	case EScene::RESULT:
		// mScene.push(new CResultScene);
		break;
	default:
		break;
	}

	return newScene;
}
