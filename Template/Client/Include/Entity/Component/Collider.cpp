#include "Collider.h"
#include "../Object/Object.h"
#include "../../Scene/Scene.h"
#include "../../Manager/CollisionManager.h"

CCollider::CCollider() :
    mProfile(nullptr),
    mColliderType(ECollider::Type::NONE),
    mIsCollided(false)
{
}

CCollider::~CCollider()
{
}

bool CCollider::Init()
{
    return true;
}

void CCollider::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);
}

void CCollider::Render(SDL_Renderer* Renderer)
{
    CComponent::Render(Renderer);
}

void CCollider::SetProfile(const std::string& name)
{
    mProfile = CCollisionManager::GetInst()->FindProfile(name);
}