#include "Collider.h"
#include "../../Object/Object.h"
#include "../../../Scene/Scene.h"
#include "../../../Manager/CollisionManager.h"
#include "../../../Scene/Collision/SceneCollision.h"

CCollider::CCollider() :
    mProfile(nullptr),
    mColliderType(ECollider::Type::NONE),
    mCollidedCount(0)
{
}

CCollider::~CCollider()
{
}

bool CCollider::Init()
{
    CComponent::Init();

    mObject->GetScene()->GetCollision()->AddCollider(this);

    return true;
}

void CCollider::OnCollisionEnter(CCollider* other)
{
    mCollidedCount++;

    for (const auto& callback : mCallbacks[ECollider::ENTER])
        callback(this, other);
}

void CCollider::OnCollisionStay(CCollider* other)
{
    for (const auto& callback : mCallbacks[ECollider::STAY])
        callback(this, other);
}

void CCollider::OnCollisionExit(CCollider* other)
{
    mCollidedCount--;

    if (mCollidedCount <= 0)
    {
        mCollidedCount = 0;

        for (const auto& callback : mCallbacks[ECollider::EXIT])
            callback(this, other);
    }
}

void CCollider::SetProfile(const std::string& name)
{
    mProfile = CCollisionManager::GetInst()->FindProfile(name);
}