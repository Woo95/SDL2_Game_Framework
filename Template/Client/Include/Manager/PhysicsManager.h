#pragma once

#include "../Core/GameInfo.h"
#include "../Core/Vector2D.h"

class CCollider;
class CBoxCollider;
class CCircleCollider;

class CPhysicsManager
{
	friend class CScene;

private:
	CPhysicsManager();
	~CPhysicsManager();

private:
	static CPhysicsManager* mInst;

	const float CONST_MinMtvLSq = 0.5f;

public:
	void ResolveOverlapIfPushable(CCollider* collider1, CCollider* collider2);

private:
	void ResolveOverlap(CCollider* collider1, CCollider* collider2, bool pushObj1, bool pushObj2);

	void ResolveAABBOverlap(CBoxCollider* collider1, CBoxCollider* collider2, bool pushObj1, bool pushObj2);
	void ResolveCircleCircleOverlap(CCircleCollider* collider1, CCircleCollider* collider2, bool pushObj1, bool pushObj2);
	void ResolveAABBCircleOverlap(CBoxCollider* collider1, CCircleCollider* collider2, bool pushObj1, bool pushObj2);

	void MoveBy(CCollider* collider, const FVector2D& mtv);

public:
	static CPhysicsManager* GetInst()
	{
		if (!mInst)
			mInst = new CPhysicsManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};