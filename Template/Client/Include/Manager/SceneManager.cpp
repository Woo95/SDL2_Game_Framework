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
	ClearScenes();

	CMemoryPoolManager::GetInst()->DeletePool<CLayer>();

	CMemoryPoolManager::GetInst()->DeletePool<CTransform>();
}

bool CSceneManager::Init()
{
	ChangeRequest(ETransition::PUSH, ESceneState::MENU);
	ChangeApply();

	return true;
}

void CSceneManager::Update(float deltaTime)
{
	if (mPending.transition != ETransition::NONE)
		ChangeApply();

	mScenes.back()->Update(deltaTime);
}

void CSceneManager::LateUpdate(float deltaTime)
{
	mScenes.back()->LateUpdate(deltaTime);
}

void CSceneManager::Render(SDL_Renderer* renderer)
{
	for (CScene* scene : mScenes)
		scene->Render(renderer);
}

void CSceneManager::ChangeApply()
{
	switch (mPending.transition)
	{
	case ETransition::PUSH:
		PushScene();
		break;
	case ETransition::POP:
		PopScene();
		break;
	case ETransition::SWAP:
		SwapScene();
		break;
	case ETransition::CLEAR:
		ClearScenes();
		break;
	case ETransition::CLEAR_THEN_PUSH:
		ClearThenPushScene();
		break;
	default:
		break;
	}

	// 새로운 씬 플래그 초기화
	mPending.transition   = ETransition::NONE;
	mPending.pendingState = ESceneState::NONE;
}

void CSceneManager::PushScene()
{
	// 새로운 씬 생성 및 리소스들 로드
	CScene* newScene = GetSceneFromState(mPending.pendingState);
	newScene->LoadResources();

	// 새로운 씬 추가
	mScenes.push_back(newScene);
	mScenes.back()->Enter();
}

void CSceneManager::PopScene()
{
	assert(!mScenes.empty());

	// 이전 씬 정리
	CScene* oldScene = mScenes.back();

	if (oldScene->Exit())
	{
		// 사용하지 않는 리소스들 언로드
		oldScene->UnloadResources();
		SAFE_DELETE(oldScene);
		mScenes.pop_back();
	}
}

void CSceneManager::SwapScene()
{
	// 새로운 씬 생성 및 리소스들 로드
	CScene* newScene = GetSceneFromState(mPending.pendingState);
	newScene->LoadResources();

	// 이전 씬 정리
	PopScene();

	// 새로운 씬 추가
	mScenes.push_back(newScene);
	mScenes.back()->Enter();
}

void CSceneManager::ClearScenes()
{
	// 이전 모든 씬 정리
	while (!mScenes.empty())
	{
		CScene* scene = mScenes.back();

		scene->UnloadResources();
		SAFE_DELETE(scene);
		mScenes.pop_back();
	}
}

void CSceneManager::ClearThenPushScene()
{
	// 새로운 씬 생성 및 리소스들 로드
	CScene* newScene = GetSceneFromState(mPending.pendingState);
	newScene->LoadResources();

	// 이전 모든 씬 정리
	ClearScenes();

	// 새로운 씬 추가
	mScenes.push_back(newScene);
	mScenes.back()->Enter();
}

CScene* CSceneManager::GetSceneFromState(ESceneState state)
{
	CScene* newScene = nullptr;

	switch (state)
	{
	case ESceneState::MENU:
		newScene = new CMenuScene;
		break;
	case ESceneState::PLAY:
		newScene = new CPlayScene;
		break;
	default:
		break;
	}
	return newScene;
}