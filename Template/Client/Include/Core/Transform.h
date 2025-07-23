#pragma once

#include "GameInfo.h"
#include "Vector2D.h"

class CTransform
{
	template <typename T>
	friend class CStaticMemoryPool;

private:
	CTransform();
	~CTransform();

private:
	CTransform* mParent = nullptr;
	std::vector<CTransform*> mChilds;

private:
	FVector2D mWorldPos;
	float     mWorldRotation;
	FVector2D mWorldScale;

	FVector2D mPivot;

	FVector2D mRelativePos;
	float     mRelativeRotation;
	FVector2D mRelativeScale;

public:
	std::vector<CTransform*>& GetChilds() { return mChilds; }
	void AddChild(CTransform* child);

public:
	const FVector2D& GetWorldPos()      const { return mWorldPos; }
	float GetWorldRotation()            const { return mWorldRotation; }
	const FVector2D& GetWorldScale()    const { return mWorldScale; }

	const FVector2D& GetPivot()         const { return mPivot; }

	const FVector2D& GetRelativePos()   const { return mRelativePos; }
	float GetRelativeRotation()         const { return mRelativeRotation; }
	const FVector2D& GetRelativeScale() const { return mRelativeScale; }

public:
	void SetWorldPos(const FVector2D& pos)
	{
		mWorldPos = pos;

		// 부모와 함께 이동 시, 새로운 상대적 위치를 계산하여 업데이트
		if (mParent)
		{
			FVector2D relativePos = mWorldPos - mParent->mWorldPos;
			mRelativePos = relativePos.GetRotate(-mParent->mWorldRotation);
		}
		else
		{
			mRelativePos = mWorldPos;
		}
		
		// 모든 자식들의 위치를 업데이트
		for (CTransform* child : mChilds)
		{
			child->SetWorldPos(child->mRelativePos + mWorldPos);
		}
	}
	void SetWorldPos(float x, float y)
	{
		SetWorldPos(FVector2D(x, y));
	}
	void SetWorldRotation(float angle)
	{
		mWorldRotation = angle;

		// 부모와 함께 회전 시, 새로운 상대적 회전 값을 계산하여 업데이트
		if (mParent)
		{
			mRelativeRotation = mWorldRotation - mParent->mWorldRotation;
		}
		else
		{
			mRelativeRotation = mWorldRotation;
		}

		// 모든 자식들의 회전 및 위치 업데이트
		for (CTransform* child : mChilds)
		{
			child->SetWorldRotation(child->mRelativeRotation + mWorldRotation);

			child->SetWorldPos(child->mRelativePos.GetRotate(mWorldRotation) + mWorldPos);
		}
	}
	void SetWorldScale(const FVector2D& scale)
	{
		mWorldScale = scale;

		// 부모와 함께 스케일링 시, 상대적 스케일을 부모의 월드 스케일로 계산
		if (mParent)
		{
			mRelativeScale.x = (mParent->mWorldScale.x == 0.0f) ? 1.0f : mWorldScale.x / mParent->mWorldScale.x;
			mRelativeScale.y = (mParent->mWorldScale.y == 0.0f) ? 1.0f : mWorldScale.y / mParent->mWorldScale.y;
		}
		else
		{
			mRelativeScale = mWorldScale;
		}

		// 모든 자식들의 스케일 및 위치 업데이트
		for (CTransform* child : mChilds)
		{
			child->SetWorldScale(child->mRelativeScale * mWorldScale);

			child->SetWorldPos(child->mRelativePos * mWorldScale + mWorldPos);
		}
	}
	void SetWorldScale(float x, float y)
	{
		SetWorldScale(FVector2D(x, y));
	}

	void SetPivot(const FVector2D& pivot)
	{
		mPivot = pivot;
	}
	void SetPivot(float x, float y) 
	{ 
		SetPivot(FVector2D(x, y)); 
	}

	void SetRelativePos(const FVector2D& pos)
	{
		mRelativePos = pos;

		// 부모와 함께 이동 시, 새로운 월드 위치를 계산하여 업데이트
		if (mParent)
		{
			mWorldPos = mRelativePos + mParent->mWorldPos;
		}
		else
		{
			mWorldPos = mRelativePos;
		}

		// 모든 자식들의 위치를 업데이트
		for (CTransform* child : mChilds)
		{
			child->SetWorldPos(child->mRelativePos + mWorldPos);
		}
	}
	void SetRelativePos(float x, float y)
	{
		SetRelativePos(FVector2D(x, y));
	}
	void SetRelativeRotation(float angle)
	{
		mRelativeRotation = angle;

		// 부모와 함께 회전 시, 새로운 월드 회전 값을 계산하여 업데이트
		if (mParent)
		{
			mWorldRotation = mRelativeRotation + mParent->mWorldRotation;
		}
		else
		{
			mWorldRotation = mRelativeRotation;
		}
		
		// 자식들의 회전 및 위치 업데이트 (위치는 SetWorldRotation()에서 바뀜)
		for (CTransform* child : mChilds)
		{
			child->mWorldPos = child->mRelativePos.GetRotate(mWorldRotation) + mWorldPos;

			float totalRotation = child->mRelativeRotation;
			CTransform* parent = mParent;
			while (parent)
			{
				totalRotation += parent->mRelativeRotation;
				parent = parent->mParent;
			}
			child->SetWorldRotation(totalRotation);
		}
	}
	void SetRelativeScale(const FVector2D& scale)
	{
		mRelativeScale = scale;

		// 부모와 함께 스케일링 시, 새로운 월드 스케일을 부모의 월드 스케일로 계산
		if (mParent)
		{
			mWorldScale = mRelativeScale * mParent->mWorldScale;
		}
		else
		{
			mWorldScale = mRelativeScale;
		}

		// 모든 자식들의 스케일 및 위치 업데이트 (위치는 SetWorldScale()에서 바뀜)
		for (CTransform* child : mChilds)
		{
			child->mWorldPos = child->mRelativePos * mWorldScale + mWorldPos;

			child->SetWorldScale(child->mRelativeScale * mWorldScale);
		}
	}
	void SetRelativeScale(float x, float y)
	{
		SetRelativeScale(FVector2D(x, y));
	}
};