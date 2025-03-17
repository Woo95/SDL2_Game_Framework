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
	ApplyChange(EScene::State::MENU);

	return true;
}

void CSceneManager::Update(float DeltaTime)
{
	mScene.top()->Update(DeltaTime);
}

void CSceneManager::LateUpdate(float DeltaTime)
{
	mScene.top()->LateUpdate(DeltaTime);

	if (mPendingScene != EScene::State::NONE)
		ApplyChange(mPendingScene);
}

void CSceneManager::Render(SDL_Renderer* Renderer)
{
	mScene.top()->Render(Renderer);
}

void CSceneManager::PendingChange(EScene::State state)
{
	mPendingScene = state;
}

void CSceneManager::ApplyChange(EScene::State state)
{
	// 새로운 씬 생성 및 리소스들 로드
	CScene* newScene = GetSceneFromState(state);
	newScene->LoadResources();

	// 이전 씬 정리
	if (!mScene.empty())
	{
		CScene* oldScene = mScene.top();

		if (oldScene->Exit())
		{
			// 사용하지 않는 리소스들 언로드
			SAFE_DELETE(oldScene);
			mScene.pop();
		}
	}

	// 새로운 씬 추가
	mScene.push(newScene);
	mScene.top()->Enter();

	// 새로운 씬 플래그 초기화
	mPendingScene = EScene::State::NONE;
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
