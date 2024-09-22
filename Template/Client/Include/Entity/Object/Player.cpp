#include "Player.h"
#include "../../Manager/MemoryPoolManager.h"

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

    // 사각형 정보 생성
    SDL_FRect    rc = { 100.f, 100.f, 200.f, 200.f };
    // 현재 렌더 색상 흰색으로 설정
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    // 사각형 그리기
    SDL_RenderDrawRectF(Renderer, &rc);
}

bool CPlayer::Release()
{
    if (CMemoryPoolManager::GetInst()->HasPool<CPlayer>())
    {
        CMemoryPoolManager::GetInst()->Deallocate<CPlayer>(this);
        return true;
    }
    return false;
}