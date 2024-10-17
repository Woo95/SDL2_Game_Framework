#pragma once

#include <math.h>

struct FVector2D
{
public:
	FVector2D() = default;
	FVector2D(float x, float y) :
		mX(x), mY(y)
	{
	}
	// copy constructor
	FVector2D(const FVector2D& refVec2D) :
		mX(refVec2D.mX),
		mY(refVec2D.mY)
	{
		//*this = refVec2D;   // alternative way.
	}
	~FVector2D() = default;

private:
	float mX;
	float mY;

public:
#pragma region MODIFICATION OPERATORS
	void operator = (const FVector2D& refVec2D)
	{
		mX = refVec2D.mX;
		mY = refVec2D.mY;
	}

	void operator += (const FVector2D& refVec2D)
	{
		mX += refVec2D.mX;
		mY += refVec2D.mY;
	}
	void operator += (float value)
	{
		mX += value;
		mY += value;
	}

	void operator -= (const FVector2D& refVec2D)
	{
		mX -= refVec2D.mX;
		mY -= refVec2D.mY;
	}
	void operator -= (float value)
	{
		mX -= value;
		mY -= value;
	}

	void operator *= (const FVector2D& refVec2D)
	{
		mX *= refVec2D.mX;
		mY *= refVec2D.mY;
	}
	void operator *= (float value)
	{
		mX *= value;
		mY *= value;
	}

	void operator /= (const FVector2D& refVec2D)
	{
		mX /= refVec2D.mX;
		mY /= refVec2D.mY;
	}
	void operator /= (float value)
	{
		mX /= value;
		mY /= value;
	}
#pragma endregion

#pragma region COMPARISON OPERATORS
	bool operator == (const FVector2D& refVec2D)	const
	{
		return mX == refVec2D.mX && mY == refVec2D.mY;
	}
	bool operator != (const FVector2D& refVec2D)	const
	{
		return mX != refVec2D.mX || mY != refVec2D.mY;
	}
#pragma endregion

#pragma region ARITHMETIC OPERATORS
	FVector2D operator + (const FVector2D& refVec2D)	const
	{
		return FVector2D(mX + refVec2D.mX, mY + refVec2D.mY);
	}
	FVector2D operator + (float value)	const
	{
		return FVector2D(mX + value, mY + value);
	}

	FVector2D operator - (const FVector2D& refVec2D)	const
	{
		return FVector2D(mX - refVec2D.mX, mY - refVec2D.mY);
	}
	FVector2D operator - (float value)	const
	{
		return FVector2D(mX - value, mY - value);
	}

	FVector2D operator * (const FVector2D& refVec2D)	const
	{
		return FVector2D(mX * refVec2D.mX, mY * refVec2D.mY);
	}
	FVector2D operator * (float value)	const
	{
		return FVector2D(mX * value, mY * value);
	}

	FVector2D operator / (const FVector2D& refVec2D)	const
	{
		return FVector2D(mX / refVec2D.mX, mY / refVec2D.mY);
	}
	FVector2D operator / (float value)	const
	{
		return FVector2D(mX / value, mY / value);
	}
#pragma endregion

public:
	float Length()	const
	{
		return sqrtf((mX * mX) + (mY * mY));
	}

	// 현재 벡터와 주어진 벡터(refVec2D) 간의 거리를 반환하는 함수
	float Distance(const FVector2D& refVec2D)	const
	{
		FVector2D diffVec = *this - refVec2D;

		return diffVec.Length();
	}

	// 현재 벡터의 방향을 유지하며, 길이를 1로 변환한 단위 벡터(unit vector)를 "바꿔주는" 함수
	void Normalize()
	{
		mX /= Length();
		mY /= Length();
	}
	// 현재 벡터의 방향을 유지하며, 길이를 1로 변환한 단위 벡터(unit vector)를 "반환하는" 함수
	FVector2D GetNormalize()	const
	{
		return *this / Length();
	}

	// 현재 벡터와 주어진 벡터(refVec2D)의 내적(Dot Product)을 계산하여 반환하는 함수
	#pragma region Dot Product Explanation
	/*
		내적 값: 두 벡터가 얼마나 같은 방향을 향하고 있는지를 나타내는 값이다.

			= -1 : 정확히 정반대 방향.	 (각도: 180)
			< 0  : 반대 방향.	         (90 < 각도 < 180)
			= 0  : 서로 수직.	         (각도: 90)
			> 0  : 같은 방향.	         (0 < 각도 < 90)
			= 1  : 정확히 동일한 방향.	 (각도: 0)
	*/
	#pragma endregion
	float Dot(const FVector2D& refVec2D)	const
	{
		return (mX * refVec2D.mX) + (mY * refVec2D.mY);
	}

	FVector2D Clamp(float left, float right, float bottom, float top)	const
	{
		return FVector2D(Clamp(mX, left, right), Clamp(mY, top, bottom));	// Clamp(mY, top, bottom)은 SDL2 좌표계에 맞춤
	}

private:
	float Clamp(float val, float min, float max)	const
	{
		if (val < min)
			return min;
		else if (val > max)
			return max;
		else
			return val;
	}
};