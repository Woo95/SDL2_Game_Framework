#include "Background.h"
#include "../../Entity/Component/SpriteComponent.h"

CBackground::CBackground()
{
}

CBackground::~CBackground()
{
}

bool CBackground::Init()
{
    // 스프라이트 컴포넌트 설정
    CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite");
    sprite->SetTexture("Stage1");
    sprite->SetFrame("Mad_Forest");
    sprite->GetTransform()->SetWorldPos(-100.f, 500.f);
    sprite->GetTransform()->SetWorldScale(4096.f, 4096.f);
    sprite->GetTransform()->SetPivot(0.5f, 0.5f);

    GetComponent()->AddChild(sprite);

    return CObject::Init();
}

void CBackground::Update(float deltaTime)
{
    CObject::Update(deltaTime);
}

void CBackground::LateUpdate(float deltaTime)
{
    CObject::LateUpdate(deltaTime);
}

void CBackground::Render(SDL_Renderer* renderer)
{
    CObject::Render(renderer);
}

void CBackground::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CBackground>(this);
}
