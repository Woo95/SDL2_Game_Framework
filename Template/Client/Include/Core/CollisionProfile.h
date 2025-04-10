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
		IGNORE,  // 충돌 무시 (감지 및 반응 없음)
		OVERLAP, // 충돌 감지만 함 (이벤트 발생, 물리 반응 없음)
		BLOCK    // 충돌 감지 + 물리 반응 (리지드바디 필요)
	};
}

// 충돌 프로필 (충돌 데이터 컨테이너)
struct FCollisionProfile
{
	using Channel = ECollisionChannel::Type;
	using Interaction = ECollisionInteraction::Type;

public:
	FCollisionProfile(const std::string& myName, Channel myChannel, Interaction defaultInteraction) :
		name(myName), channel(myChannel)
	{
		for (int channel = 0; channel < Channel::END; channel++)
			collisionResponses[channel] = defaultInteraction;
	}

public:
	std::string name;
	Channel channel;
	Interaction collisionResponses[Channel::END];
};