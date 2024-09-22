#include "Monster.h"
#include "../../Manager/MemoryPoolManager.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
    if (!CObject::Init())
        return false;

    return true;
}

void CMonster::Update(float DeltaTime)
{
    CObject::Update(DeltaTime);
}

void CMonster::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);

    // 사각형 정보 생성
    SDL_FRect    rc = { 800.f, 200.f, 100.f, 100.f };
    // 현재 렌더 색상 흰색으로 설정
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    // 사각형 그리기
    SDL_RenderDrawRectF(Renderer, &rc);
}

bool CMonster::Release()
{
    if (CMemoryPoolManager::GetInst()->HasPool<CMonster>())
    {
        CMemoryPoolManager::GetInst()->Deallocate<CMonster>(this);
        return true;
    }
    return false;
}