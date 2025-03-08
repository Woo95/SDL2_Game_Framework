#pragma once

#include "../Component.h"
#include "../../../Core/CollisionProfile.h"
#include "../../../Core/Vector2D.h"

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
	FCollisionProfile*  mProfile;
	ECollider::Type     mColliderType;

	int                 mCollidedCount;
	bool	            mIsCollided;
	FVector2D           mHitPoint;

	//std::function<void(CCollider*, CCollider*)> mCollisionFunc; // todo

protected:
	virtual bool Init()                         override;
	virtual void Update(float DeltaTime)        override;
	virtual void LateUpdate(float DeltaTime)    override;
	virtual void Render(SDL_Renderer* Renderer) override;
	virtual void Release() = 0;

public:
	virtual bool Intersect(CCollider* other) = 0;
	virtual void OnCollisionEnter(CCollider* other);
	virtual void OnCollisionStay(CCollider* other);
	virtual void OnCollisionExit(CCollider* other);

public:
	FCollisionProfile* GetProfile()   const { return mProfile; }
	ECollider::Type GetColliderType() const { return mColliderType; }
	bool IsCollided()                 const { return mIsCollided; }

	void SetProfile(const std::string& name);
};