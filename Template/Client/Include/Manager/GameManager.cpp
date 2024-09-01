#include "GameManager.h"
#include "../Core/Timer.h"
#include "../Core/Input.h"
#include "SceneManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
    CInput::DestroyInst();

    CSceneManager::DestroyInst();

    SDL_DestroyRenderer(mRenderer);

    SDL_DestroyWindow(mWindow);

    SDL_Quit();
}

bool CGameManager::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    mWindow = SDL_CreateWindow("Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (!mWindow)
        return false;

    mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
    if (!mRenderer)
        return false;

    CTimer::Init();

    if (!CInput::GetInst()->Init())
        return false;

    if (!CSceneManager::GetInst()->Init())
        return false;

    return true;
}

int CGameManager::Run()
{
    SDL_Event event;

    while (mLoop)
    {
        // 이벤트가 있을 경우...
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                // 종료 요청시
                case SDL_QUIT:  
                    mLoop = false;
                    break;
                default:
                    break;
            }
        }
        Logic();
    }

    return 0;
}

void CGameManager::Logic()
{
    Update();

    Render();
}

void CGameManager::Update()
{
    CTimer::Update();

    CInput::GetInst()->Update();

    CSceneManager::GetInst()->Update(CTimer::GetDeltaTime());
}

void CGameManager::Render()
{
    CSceneManager::GetInst()->Render(mRenderer);
}