#include "Engine.h"
#include "Core/Timer.h"
#include "Manager/MemoryPoolManager.h"
#include "Manager/InputManager.h"
#include "Manager/CollisionManager.h"
#include "Manager/PhysicsManager.h"
#include "Manager/EventManager.h"
#include "Manager/SceneManager.h"
#include "Manager/Data/PathManager.h"
#include "Manager/Data/Resource/AssetManager.h"
#include "Core/DataLoader.h"

CEngine* CEngine::mInst = nullptr;

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
    CSceneManager::DestroyInst();
    
    CEventManager::DestroyInst();

    CPhysicsManager::DestroyInst();

    CCollisionManager::DestroyInst();

    CAssetManager::DestroyInst();

	CPathManager::DestroyInst();

	CInputManager::DestroyInst();

	CTimer::DestroyInst();

	CMemoryPoolManager::DestroyInst();

    SDL_DestroyRenderer(mRenderer);

    SDL_DestroyWindow(mWindow);

    SDL_Quit();
}

bool CEngine::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    mWindow = SDL_CreateWindow("Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 800, SDL_WINDOW_SHOWN);
    if (!mWindow)
        return false;

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (!mRenderer)
        return false;

    if (!CInputManager::GetInst()->Init())
        return false;

    if (!CPathManager::GetInst()->Init())
        return false;

    CDataLoader dataLoader;
    if (!dataLoader.Init())
        return false;

    if (!CCollisionManager::GetInst()->Init())
        return false;

    if (!CSceneManager::GetInst()->Init())
        return false;

    return true;
}

void CEngine::Run()
{
    SDL_Event event;

    while (mLoop)
    {
        // 이벤트가 있을 경우...
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			mLoop = false;

		Update();

		LateUpdate();

		Render();
    }
}

void CEngine::Update()
{
    CTimer::GetInst()->Update();

    CInputManager::GetInst()->Update();

    CEventManager::GetInst()->Update(CTimer::GetInst()->GetDeltaTime());

    CSceneManager::GetInst()->Update(CTimer::GetInst()->GetDeltaTime());
}

void CEngine::LateUpdate()
{
    CSceneManager::GetInst()->LateUpdate(CTimer::GetInst()->GetDeltaTime());
}

void CEngine::Render()
{
    // 현재 렌더 색상 검정으로 설정
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    // 현재 색상으로 화면 지우기
    SDL_RenderClear(mRenderer);

    CSceneManager::GetInst()->Render(mRenderer);

    // 렌더링한 내용을 화면에 표시
    SDL_RenderPresent(mRenderer);
}