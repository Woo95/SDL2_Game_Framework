#pragma once

#include <string>

// 충돌 채널들
namespace ECollisionChannel
{
	enum Type : unsigned char
	{
		DEFAULT,
		PLAYER,
		MONSTER,
		BULLET,
		END
	};
}

// 충돌 상호작용 유형들
namespace ECollisionInteraction
{
	enum Type : unsigned char
	{
		DISABLE_COLLISION,
		ENABLE_COLLISION
	};
}

// 충돌 프로필 (충돌 데이터 컨테이너)
struct FCollisionProfile
{
public:
	FCollisionProfile() :
		mChannel(ECollisionChannel::DEFAULT)
	{
		for (int i = 0; i < ECollisionChannel::END; ++i)
		{
			mInteractArr[i] = ECollisionInteraction::DISABLE_COLLISION;
		}
	}

public:
	std::string                 mProfileName;
	ECollisionChannel::Type     mChannel;
	ECollisionInteraction::Type mInteractArr[ECollisionChannel::END];
};