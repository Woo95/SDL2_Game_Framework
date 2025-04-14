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
	FVector2D           mHitPoint;

	using Callback = std::function<void(CCollider*, CCollider*)>;
	std::vector<Callback> mOnEnterFuncs;
	std::vector<Callback> mOnStayFuncs;
	std::vector<Callback> mOnExitFuncs;

protected:
	virtual bool Init()                         override;
	virtual void Update(float DeltaTime)        override;
	virtual void LateUpdate(float DeltaTime)    override;
	virtual void Render(SDL_Renderer* Renderer) override;
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
	void AddCallbackFuncOnEnter(T* obj, void(T::*func)(CCollider*, CCollider*))
	{
		// [캡처리스트](매개변수) -> 반환타입 { 함수 본문 }
		Callback cb = [obj, func](CCollider* col1, CCollider* col2) { (obj->*func)(col1, col2); };

		mOnEnterFuncs.emplace_back(cb);
	}	
	template <typename T>
	void AddCallbackFuncOnStay(T* obj, void(T::* func)(CCollider*, CCollider*))
	{
		// [캡처리스트](매개변수) -> 반환타입 { 함수 본문 }
		Callback cb = [obj, func](CCollider* col1, CCollider* col2) { (obj->*func)(col1, col2); };

		mOnStayFuncs.emplace_back(cb);
	}
	template <typename T>
	void AddCallbackFuncOnExit(T* obj, void(T::* func)(CCollider*, CCollider*))
	{
		// [캡처리스트](매개변수) -> 반환타입 { 함수 본문 }
		Callback cb = [obj, func](CCollider* col1, CCollider* col2) { (obj->*func)(col1, col2); };

		mOnExitFuncs.emplace_back(cb);
	}

public:
	FCollisionProfile* GetProfile()   const { return mProfile; }
	ECollider::Type GetColliderType() const { return mColliderType; }
	bool IsCollided() const { return mCollidedCount > 0; }

	void SetProfile(const std::string& name);
};