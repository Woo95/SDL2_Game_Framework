#include "CollisionManager.h"
#include "../Entity/Component/BoxCollider.h"
#include "../Entity/Component/CircleCollider.h"

CCollisionManager* CCollisionManager::mInst = nullptr;

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	std::unordered_map<std::string, FCollisionProfile*>::iterator iter    = mProfileMap.begin();
	std::unordered_map<std::string, FCollisionProfile*>::iterator iterEnd = mProfileMap.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("TestProfile", ECollisionChannel::DEFAULT, ECollisionInteraction::ENABLE_COLLISION);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& name, ECollisionChannel::Type channel, ECollisionInteraction::Type interaction)
{
	if (FindProfile(name))	// exist
		return false;

	FCollisionProfile* profile = new FCollisionProfile;

	profile->mProfileName = name;
	profile->mChannel     = channel;
	for (int i = 0; i < ECollisionChannel::END; i++)
	{
		profile->mInteractArr[i] = interaction;
	}

	mProfileMap[name] = profile;

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& name, ECollisionChannel::Type channel, ECollisionInteraction::Type interaction)
{
	FCollisionProfile* profile = FindProfile(name);
	if (!profile)
		return false;

	profile->mInteractArr[channel] = interaction;

	return true;
}

FCollisionProfile* CCollisionManager::FindProfile(const std::string& name)
{
	std::unordered_map<std::string, FCollisionProfile*>::iterator iter    = mProfileMap.find(name);
	std::unordered_map<std::string, FCollisionProfile*>::iterator iterEnd = mProfileMap.end();

	if (iter != iterEnd)
		return iter->second;
	else
		return nullptr;
}

bool CCollisionManager::AABBCollision(CBoxCollider* collider1, CBoxCollider* collider2)
{
	const SDL_FRect& box1 = collider1->GetRect();
	const SDL_FRect& box2 = collider2->GetRect();

	if (box1.x + box1.w < box2.x ||
		box1.x > box2.x + box2.w ||
		box1.y + box1.h < box2.y ||
		box1.y > box2.y + box2.h)
	{
		return false;
	}

	FVector2D hitPoint;
	hitPoint.mX = (std::max(box1.x, box2.x) + std::min(box1.x + box1.w, box2.x + box2.w)) * 0.5f;
	hitPoint.mY = (std::max(box1.y, box2.y) + std::min(box1.y + box1.h, box2.y + box2.h)) * 0.5f;

	collider1->mHitPoint = hitPoint;
	collider2->mHitPoint = hitPoint;

	return true;
}

bool CCollisionManager::CircleCircleCollision(CCircleCollider* collider1, CCircleCollider* collider2)
{
	const FCircle& circle1 = collider1->GetCircle();
	const FCircle& circle2 = collider2->GetCircle();

	float distance  = circle1.mCenter.Distance(circle2.mCenter);
	float sumRadius = circle1.mRadius + circle2.mRadius;

	if (distance > sumRadius)
	{
		return false;
	}

	FVector2D hitPoint = (circle1.mCenter + circle2.mCenter) * 0.5f;

	collider1->mHitPoint = hitPoint;
	collider2->mHitPoint = hitPoint;

	return true;
}

bool CCollisionManager::AABBCircleCollision(CBoxCollider* collider1, CCircleCollider* collider2)
{
	const SDL_FRect& box  = collider1->GetRect();
	const FCircle& circle = collider2->GetCircle();

	// 원의 중심에서 사각형 테두리를 기준으로 가장 가까운 점을 찾는다.
	FVector2D closestPointOnBox = circle.mCenter.Clamp(box.x, box.x + box.w, box.y + box.h, box.y);

	// 원의 중심과 그 점의 거리를 찾는다.
	float distance = circle.mCenter.Distance(closestPointOnBox);

	if (circle.mRadius < distance)
	{
		return false;
	}

	FVector2D hitPoint = closestPointOnBox;

	collider1->mHitPoint = hitPoint;
	collider2->mHitPoint = hitPoint;

	return true;
}

bool CCollisionManager::AABBPointCollision(CBoxCollider* collider, const FVector2D& point)
{
	const SDL_FRect& box = collider->GetRect();

	if (box.x + box.w < point.mX ||
		box.x > point.mX         ||
		box.y + box.h < point.mY ||
		box.y > point.mY)
	{
		return false;
	}

	collider->mHitPoint = point;

	return true;

}

bool CCollisionManager::CirclePointCollision(CCircleCollider* collider, const FVector2D& point)
{
	const FCircle& circle = collider->GetCircle();

	if (circle.mCenter.Distance(point) > circle.mRadius)
	{
		return false;
	}

	collider->mHitPoint = point;

	return true;
}
