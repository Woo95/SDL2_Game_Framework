#include "PhysicsManager.h"
#include "../Entity/Object/Object.h"
#include "../Core/Transform.h"
#include "../Entity/Component/Collider/BoxCollider.h"
#include "../Entity/Component/Collider/CircleCollider.h"
#include "../Entity/Component/Rigidbody.h"

CPhysicsManager* CPhysicsManager::mInst = nullptr;

CPhysicsManager::CPhysicsManager()
{
}

CPhysicsManager::~CPhysicsManager()
{
}

void CPhysicsManager::ResolveOverlap(CCollider* collider1, CCollider* collider2, bool pushObj1, bool pushObj2)
{
    ECollider::Type type1 = collider1->GetColliderType();
    ECollider::Type type2 = collider2->GetColliderType();

    if (type1 == ECollider::Type::BOX && type2 == ECollider::Type::BOX)
    {
        CBoxCollider* box1 = static_cast<CBoxCollider*>(collider1);
        CBoxCollider* box2 = static_cast<CBoxCollider*>(collider2);

        ResolveAABBOverlap(box1, box2, pushObj1, pushObj2);
    }
    else if (type1 == ECollider::Type::CIRCLE && type2 == ECollider::Type::CIRCLE)
    {
        CCircleCollider* circle1 = static_cast<CCircleCollider*>(collider1);
        CCircleCollider* circle2 = static_cast<CCircleCollider*>(collider2);

        ResolveCircleCircleOverlap(circle1, circle2, pushObj1, pushObj2);
    }
    else if (type1 == ECollider::Type::BOX && type2 == ECollider::Type::CIRCLE)
    {
        CBoxCollider*    box    = static_cast<CBoxCollider*>(collider1);
        CCircleCollider* circle = static_cast<CCircleCollider*>(collider2);

        ResolveAABBCircleOverlap(box, circle, pushObj1, pushObj2);
    }
    else if (type2 == ECollider::Type::BOX && type1 == ECollider::Type::CIRCLE)
    {
        CBoxCollider*    box    = static_cast<CBoxCollider*>(collider2);
        CCircleCollider* circle = static_cast<CCircleCollider*>(collider1);

        ResolveAABBCircleOverlap(box, circle, pushObj2, pushObj1);
    }
}

void CPhysicsManager::ResolveAABBOverlap(CBoxCollider* collider1, CBoxCollider* collider2, bool pushObj1, bool pushObj2)
{
    // 두 사각형 정보 가져오기
    const SDL_FRect& box1 = collider1->GetRect();
    const SDL_FRect& box2 = collider2->GetRect();

    // 두 사각형 중심점 계산
    FVector2D center1(box1.x + box1.w * 0.5f, box1.y + box1.h * 0.5f);
    FVector2D center2(box2.x + box2.w * 0.5f, box2.y + box2.h * 0.5f);

    // 두 사각형 중심점 간의 벡터 계산
    FVector2D delta = center1 - center2;

    // 각 축의 겹침 정도 계산
    float overlapX = (box1.w + box2.w) * 0.5f - std::abs(delta.x);
    float overlapY = (box1.h + box2.h) * 0.5f - std::abs(delta.y);

    // 최소 이동 벡터(MTV) 계산
    FVector2D mtv;
    if (overlapX < overlapY)
        mtv = FVector2D((delta.x < 0 ? -overlapX : overlapX), 0.f);
    else
        mtv = FVector2D(0.f, (delta.y < 0 ? -overlapY : overlapY));

    // MTV가 작으면 접촉 상태로 간주하고 무시
    if (mtv.LengthSquared() < CONST_MinMtvLSq)
        return;

    // 겹쳐진 오브젝트들 MTV 방향으로 이동
    if (pushObj1)
        MoveBy(collider1, mtv);
    if (pushObj2)
        MoveBy(collider2, -mtv);
}

void CPhysicsManager::ResolveCircleCircleOverlap(CCircleCollider* collider1, CCircleCollider* collider2, bool pushObj1, bool pushObj2)
{
    // 두 원형 정보 가져오기
    const FCircle& circle1 = collider1->GetCircle();
    const FCircle& circle2 = collider2->GetCircle();

    // 두 원형 중심점 간의 벡터 계산
    FVector2D delta = circle1.center - circle2.center;

    // 두 중심점 간의 거리 계산
    float distance = delta.Length();

    // 겹침 정도 계산
    float overlap = circle1.radius + circle2.radius - distance;

    // 최소 이동 벡터(MTV) 계산
    FVector2D mtv = delta.GetNormalize() * overlap;

    // MTV가 작으면 접촉 상태로 간주하고 무시
    if (mtv.LengthSquared() < CONST_MinMtvLSq)
        return;

    // 겹쳐진 오브젝트들 MTV 방향으로 이동
    if (pushObj1)
        MoveBy(collider1, mtv);
    if (pushObj2)
        MoveBy(collider2, -mtv);
}

void CPhysicsManager::ResolveAABBCircleOverlap(CBoxCollider* collider1, CCircleCollider* collider2, bool pushObj1, bool pushObj2)
{
    // 사각형과 원형의 정보 가져오기
    const SDL_FRect& box  = collider1->GetRect();
    const FCircle& circle = collider2->GetCircle();

    // 사각형 중심점 계산
    FVector2D boxCenter(box.x + box.w * 0.5f, box.y + box.h * 0.5f);

    // 사각형과 원형 중심점 간의 벡터 계산
    FVector2D delta = boxCenter - circle.center;

    // 각 축의 겹침 정도 계산
    float overlapX = (box.w * 0.5f + circle.radius) - std::abs(delta.x);
    float overlapY = (box.h * 0.5f + circle.radius) - std::abs(delta.y);

    // 최소 이동 벡터(MTV) 계산
    FVector2D mtv;
    if (overlapX < overlapY)
        mtv = FVector2D((delta.x < 0 ? -overlapX : overlapX), 0.f);
    else
        mtv = FVector2D(0.f, (delta.y < 0 ? -overlapY : overlapY));

    // MTV가 작으면 접촉 상태로 간주하고 무시
    if (mtv.LengthSquared() < CONST_MinMtvLSq)
        return;

    // 겹쳐진 오브젝트들 MTV 방향으로 이동
    if (pushObj1)
        MoveBy(collider1, mtv);
    if (pushObj2)
        MoveBy(collider2, -mtv);
}

void CPhysicsManager::MoveBy(CCollider* collider, const FVector2D& mtv)
{
    if (CTransform* transform = collider->GetObject()->GetTransform())
    {
        // 현재 상대 위치(Relative Position)를 가져와 MTV만큼 이동
        FVector2D newRelativePos = transform->GetRelativePos() + mtv;

        // 상대적 위치를 업데이트 (월드 위치는 내부적으로 갱신됨)
        transform->SetRelativePos(newRelativePos);
    }
}