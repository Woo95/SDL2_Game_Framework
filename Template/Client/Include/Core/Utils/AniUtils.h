#pragma once

#include "../GameInfo.h"

enum class EAnimationType : unsigned char
{
	NONE,
	TIME,
	MOVE
};

enum class EAnimationState : unsigned char
{
	NONE,

	IDLE,
	WALK,
	JUMP,

	VFX
};

struct FAnimationData
{
	EAnimationType type = EAnimationType::NONE;

	bool  isLoop = 0;
	float intervalPerFrame = 0;

	std::vector<SDL_Rect> frames;
};