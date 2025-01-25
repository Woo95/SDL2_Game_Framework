#pragma once

#include "../Core/AniUtils.h"

class CSpriteComponent;
class CTexture;

class CAnimation
{
	friend class CSpriteComponent;

public:
	CAnimation();
	~CAnimation();

protected:
	CSpriteComponent* mOwner = nullptr;

	std::unordered_map<EAnimationState, FAnimationStateInfo> mAnimationStates;

	EAnimationType  mCurrentType  = EAnimationType::NONE;
	EAnimationState mCurrentState = EAnimationState::NONE;
	float mFrameInterval = 0.0f;

public:
	void Update(float DeltaTime);

public:
	void AddFrame(EAnimationState state, SDL_Rect& frame);
	void AddFrames(EAnimationState state, std::vector<SDL_Rect>& frames);

	const SDL_Rect& GetCurrentFrame() { return mAnimationStates[mCurrentState].GetFrame(); }

	void SetCurrentType(EAnimationType type) 
	{ 
		mCurrentType = type;
	}
	void SetCurrentState(EAnimationState state)
	{
		if (mCurrentState != state)
		{
			mCurrentState = state;
			mAnimationStates[state].currentIdx = 0;
			mFrameInterval = 0.0f;
		}
	};

	void SetAnimationStateInfo(EAnimationState state, bool loop, float time)
	{
		mAnimationStates[state].isLoop = loop;
		mAnimationStates[state].IntervalPerFrame = time;
	}
};