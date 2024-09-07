#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    if (!CObject::Init())
        return false;

	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CObject::Update(DeltaTime);
}

void CPlayer::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);

    // 현재 렌더 색상 검정으로 설정
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    // 현재 색상으로 화면 지우기
    SDL_RenderClear(Renderer);

    // 사각형 정보 생성
    SDL_FRect    rc = { 100.f, 100.f, 200.f, 200.f };
    // 현재 렌더 색상 흰색으로 설정
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    // 사각형 그리기
    SDL_RenderDrawRectF(Renderer, &rc);

    // 렌더링한 내용을 화면에 표시
    SDL_RenderPresent(Renderer);
}
