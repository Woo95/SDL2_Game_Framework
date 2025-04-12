#pragma once

#include <cmath>

#define M_PI_F 3.141593f

struct FVector2D
{
public:
	// 아래 정적 벡터 변수들은 자주 사용되는 벡터들을 매번 생성하지 않고 재사용하기 위해 전역적으로 정의한다.
	static FVector2D ZERO;
	static FVector2D UP;
	static FVector2D DOWN;
	static FVector2D LEFT;
	static FVector2D RIGHT;

public:
	FVector2D() = default;
	FVector2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	// copy constructor
	FVector2D(const FVector2D& refVec2D)
	{
		*this = refVec2D;
	}
	~FVector2D() = default;

public:
	float x;
	float y;

public:
#pragma region MODIFICATION OPERATORS
	void operator = (const FVector2D& refVec2D)
	{
		x = refVec2D.x;
		y = refVec2D.y;
	}

	void operator += (const FVector2D& refVec2D)
	{
		x += refVec2D.x;
		y += refVec2D.y;
	}
	void operator += (float value)
	{
		x += value;
		y += value;
	}

	void operator -= (const FVector2D& refVec2D)
	{
		x -= refVec2D.x;
		y -= refVec2D.y;
	}
	void operator -= (float value)
	{
		x -= value;
		y -= value;
	}

	void operator *= (const FVector2D& refVec2D)
	{
		x *= refVec2D.x;
		y *= refVec2D.y;
	}
	void operator *= (float value)
	{
		x *= value;
		y *= value;
	}

	void operator /= (const FVector2D& refVec2D)
	{
		x /= refVec2D.x;
		y /= refVec2D.y;
	}
	void operator /= (float value)
	{
		x /= value;
		y /= value;
	}
#pragma endregion

#pragma region COMPARISON OPERATORS
	bool operator == (const FVector2D& refVec2D)	const
	{
		return x == refVec2D.x && y == refVec2D.y;
	}
	bool operator != (const FVector2D& refVec2D)	const
	{
		return x != refVec2D.x || y != refVec2D.y;
	}
#pragma endregion

#pragma region ARITHMETIC OPERATORS
	FVector2D operator - () const
	{
		return FVector2D(-x, -y);
	}

	FVector2D operator + (const FVector2D& refVec2D)	const
	{
		return FVector2D(x + refVec2D.x, y + refVec2D.y);
	}
	FVector2D operator + (float value)	const
	{
		return FVector2D(x + value, y + value);
	}

	FVector2D operator - (const FVector2D& refVec2D)	const
	{
		return FVector2D(x - refVec2D.x, y - refVec2D.y);
	}
	FVector2D operator - (float value)	const
	{
		return FVector2D(x - value, y - value);
	}

	FVector2D operator * (const FVector2D& refVec2D)	const
	{
		return FVector2D(x * refVec2D.x, y * refVec2D.y);
	}
	FVector2D operator * (float value)	const
	{
		return FVector2D(x * value, y * value);
	}

	FVector2D operator / (const FVector2D& refVec2D)	const
	{
		return FVector2D(x / refVec2D.x, y / refVec2D.y);
	}
	FVector2D operator / (float value)	const
	{
		return FVector2D(x / value, y / value);
	}
#pragma endregion

public:
	float Length()	const
	{
		return sqrtf((x * x) + (y * y));
	}

	// 현재 벡터와 주어진 벡터(refVec2D) 간의 거리를 반환하는 함수
	float Distance(const FVector2D& refVec2D)	const
	{
		FVector2D diffVec = *this - refVec2D;

		return diffVec.Length();
	}

	// 현재 벡터의 방향을 유지하며, 길이를 1로 변환한 단위 벡터(unit vector)를 "바꿔주는" 함수
	void SetNormalize()
	{
		x /= Length();
		y /= Length();
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
		return (x * refVec2D.x) + (y * refVec2D.y);
	}

	FVector2D Clamp(float left, float right, float bottom, float top)	const
	{
		return FVector2D(Clamp(x, left, right), Clamp(y, top, bottom));	// Clamp(y, top, bottom)은 SDL2 좌표계에 맞춤
	}

	// 주어진 각도만큼 벡터를 회전시켜서 현재 벡터를 갱신하는 함수
	void SetRotate(float angle)
	{
		float radian = angle * M_PI_F / 180.0f;
		
		x = x * cosf(radian) - y * sinf(radian);
		y = x * sinf(radian) + y * cosf(radian);
	}
	// 주어진 각도만큼 벡터를 회전시킨 새로운 벡터를 반환하는 함수
	FVector2D GetRotate(float angle)	const
	{
		float radian = angle * M_PI_F / 180.0f;

		return FVector2D(x * cosf(radian) - y * sinf(radian), x * sinf(radian) + y * cosf(radian));
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