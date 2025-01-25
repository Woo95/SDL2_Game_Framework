#pragma once

#include "GameInfo.h"

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
	JUMP
};

struct FAnimationStateInfo
{
    bool  isLoop = true;
    float IntervalPerFrame = 0.1f;

    std::vector<SDL_Rect> frames;
    int currentIdx = 0;

    const SDL_Rect& GetFrame() const
    {
        return frames[currentIdx];
    }
};