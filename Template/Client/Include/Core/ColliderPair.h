#pragma once

#include "GameInfo.h"

class CCollider;

namespace EPair
{
	enum Status : unsigned char
	{
		DNE,
		COLLIDED,
		NOT_COLLIDED
	};
}

struct FColliderPair
{
public:
	CCollider* collider1;
	CCollider* collider2;

public:
	bool operator == (const FColliderPair& other) const
	{
		return (collider1 == other.collider1 && collider2 == other.collider2) ||
			   (collider1 == other.collider2 && collider2 == other.collider1);
	}
};

// FPair를 unordered 컨테이너의 키로 사용하기 위한 std::hash 템플릿 특수화
template <>
struct std::hash<FColliderPair>
{
private:
	// smhasher by rurban
	size_t mix(size_t hash) const
	{
		hash ^= hash >> 23;
		hash *= 0x2127599bf4325c37ULL;
		hash ^= hash >> 47;

		return hash;
	}

public:
	size_t operator () (const FColliderPair& pair) const noexcept
	{
		size_t hash1 = std::hash<CCollider*>()(pair.collider1);
		size_t hash2 = std::hash<CCollider*>()(pair.collider2);

		size_t combinedHash = mix(hash1) ^ mix(hash2);

		return combinedHash;
	}
};