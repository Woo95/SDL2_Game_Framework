#include "Background.h"
#include "../../Entity/Component/Sprite/SpriteComponent.h"

CBackground::CBackground()
{
}

CBackground::~CBackground()
{
}

bool CBackground::Init()
{
    if (!CObject::Init())
        return false;

    // 스프라이트 컴포넌트 만들기
    CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite", mRootComponent);
    sprite->SetTexture("Stage1");
    sprite->SetSprite("Mad_Forest");

    // 위치 설정 (스프라이트 컴포넌트)
    CTransform* spriteTrans = sprite->GetTransform();
    spriteTrans->SetWorldPos(-100.f, 500.f);
    spriteTrans->SetWorldScale(4096.f, 4096.f);
    spriteTrans->SetPivot(0.5f, 0.5f);

    return true;
}

void CBackground::Update(float DeltaTime)
{
    CObject::Update(DeltaTime);
}

void CBackground::LateUpdate(float DeltaTime)
{
    CObject::LateUpdate(DeltaTime);
}

void CBackground::Render(SDL_Renderer* Renderer)
{
    CObject::Render(Renderer);
}

void CBackground::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CBackground>(this);
}
