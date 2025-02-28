#pragma once

#include "../Core/GameInfo.h"
#include "../Core/CollisionProfile.h"
#include "../Core/Vector2D.h"

class CBoxCollider; 
class CCircleCollider;
class CWidgetBase;

/* 
CollisionManager: 충돌 계산 및 프로필 저장.
	- 게임 내 모든 충돌 관련 프로필을 저장하고 관리함.
	- 충돌 계산 알고리즘을 제공하며, 다양한 충돌체의 충돌 여부를 판별함.
*/
class CCollisionManager // Profile and Collision Handler
{
private:
	CCollisionManager();
	~CCollisionManager();

private:
	std::unordered_map<std::string, FCollisionProfile*>	mProfileMap;

	static CCollisionManager* mInst;

public:
	bool Init();

	bool CreateProfile(const std::string& name, ECollisionChannel::Type channel, 
		ECollisionInteraction::Type interaction = ECollisionInteraction::ENABLE_COLLISION);

	bool SetCollisionInteraction(const std::string& name, ECollisionChannel::Type channel,
		ECollisionInteraction::Type interaction = ECollisionInteraction::ENABLE_COLLISION);

	FCollisionProfile* FindProfile(const std::string& name);

public:
	bool AABBCollision(CBoxCollider* collider1, CBoxCollider* collider2);
	bool CircleCircleCollision(CCircleCollider* collider1, CCircleCollider* collider2);
	bool AABBCircleCollision(CBoxCollider* collider1, CCircleCollider* collider2);
	bool AABBPointCollision(CBoxCollider* collider, const FVector2D& point);
	bool CirclePointCollision(CCircleCollider* collider, const FVector2D& point);

	bool AABBPointCollision(const SDL_Rect& rect, const FVector2D& point); // for the ui

public:
	static CCollisionManager* GetInst()
	{
		if (!mInst)
			mInst = new CCollisionManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};