#include "Collider.h"
#include "../../Object/Object.h"
#include "../../../Scene/Scene.h"
#include "../../../Manager/CollisionManager.h"
#include "../../../Scene/Collision/SceneCollision.h"

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
    mObject->GetScene()->GetCollision()->AddCollider(this);

    return true;
}

void CCollider::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);
}

void CCollider::LateUpdate(float DeltaTime)
{
    CComponent::LateUpdate(DeltaTime);
}

void CCollider::Render(SDL_Renderer* Renderer)
{
    CComponent::Render(Renderer);
}

void CCollider::OnCollisionEnter(CCollider* other)
{
    mIsCollided = true;
}

void CCollider::OnCollisionStay(CCollider* other)
{
    mIsCollided = true;
}

void CCollider::OnCollisionExit(CCollider* other)
{
    mIsCollided = false;
}

void CCollider::SetProfile(const std::string& name)
{
    mProfile = CCollisionManager::GetInst()->FindProfile(name);
}