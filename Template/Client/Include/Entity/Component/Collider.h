#pragma once

#include "Component.h"
#include "../../Core/CollisionProfile.h"
#include "../../Core/Vector2D.h"

namespace ECollider
{
	enum Type : unsigned char
	{
		NONE,
		BOX,
		CIRCLE
	};
}

class CCollider abstract : public CComponent
{
	friend class CCollisionManager;

public:
	CCollider();
	virtual ~CCollider();

protected:
	FCollisionProfile*	mProfile;
	ECollider::Type		mColliderType;

	bool				mIsCollided;
	FVector2D			mHitPoint;

	//std::function<void(CCollider*, CCollider*)> mCollisionFunc; // todo

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
	virtual void Release() = 0;

	virtual bool Intersect(CCollider* other) = 0;
	virtual void OnCollision(CCollider* other);

public:
	FCollisionProfile* GetProfile()   const { return mProfile; }
	ECollider::Type GetColliderType() const { return mColliderType; }
	bool IsCollided()                 const { return mIsCollided; }

	void SetProfile(const std::string& name);
};