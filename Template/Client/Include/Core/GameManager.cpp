#include "GameManager.h"
#include "Timer.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
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
    DestroyInst();

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
}

void CGameManager::Render()
{
    // 현재 렌더 색상 검정으로 설정
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    // 현재 색상으로 화면 지우기
    SDL_RenderClear(mRenderer);

    // 사각형 정보 생성
    SDL_FRect    rc = {100.f, 100.f, 200.f, 200.f};
    // 현재 렌더 색상 흰색으로 설정
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    // 사각형 그리기
    SDL_RenderDrawRectF(mRenderer, &rc);

    // 렌더링한 내용을 화면에 표시
    SDL_RenderPresent(mRenderer);
}