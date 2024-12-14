#include "Collider.h"
#include "../Object/Object.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Collision/SceneCollision.h"

CCollider::CCollider() :
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