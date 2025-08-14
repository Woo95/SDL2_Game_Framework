#pragma once

#include "../Component.h"
#include "../../../Core/Utils/ColliderUtils.h"
#include "../../../Core/CollisionProfile.h"
#include "../../../Core/Vector2D.h"

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
	FVector2D           mHitPoint;

	using Callback = std::function<void(CCollider*, CCollider*)>;
	std::vector<Callback> mCallbacks[ECollider::OnCollision::MAX];

protected:
	virtual bool Init() override;
	virtual void Release() = 0;

public:
	virtual bool Intersect(CCollider* other) = 0;
	
public:
	// Executers //
	void OnCollisionEnter(CCollider* other);
	void OnCollisionStay(CCollider* other);
	void OnCollisionExit(CCollider* other);

	// Binders //
	template <typename T>
	void AddCallbackFunc(ECollider::OnCollision event, T* obj, void(T::* func)(CCollider*, CCollider*))
	{
		// [캡처리스트](매개변수) -> 반환타입 { 함수 본문 }
		Callback cb = [obj, func](CCollider* col1, CCollider* col2) { (obj->*func)(col1, col2); };

		mCallbacks[event].emplace_back(cb);
	}

public:
	ECollider::Type GetColliderType() const { return mColliderType; }
	const FVector2D&   GetHitPoint()  const { return mHitPoint; }
	FCollisionProfile* GetProfile()   const { return mProfile; }

	void SetProfile(const std::string& name);

	bool IsCollided() const
	{ 
		return mCollidedCount > 0; 
	}
};