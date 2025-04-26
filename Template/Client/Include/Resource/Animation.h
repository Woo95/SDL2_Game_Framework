#pragma once

#include "../Core/Utils/AniUtils.h"
#include "../Core/Vector2D.h"

class CSpriteComponent;
class CTexture;

class CAnimation
{
	friend class CAnimationManager;
	friend class CSpriteComponent;

public:
	CAnimation();
	~CAnimation();

protected:
	CSpriteComponent* mOwner;

	std::unordered_map<EAnimationState, std::shared_ptr<FAnimationData>> mAnimationStates;

	EAnimationState mCurrentState;

	FVector2D mPrevPos;

	float mFrameInterval;
	int   mCurrIdx;

public:
	void Update(float deltaTime);

public:
	const SDL_Rect& GetCurrentFrame()
	{ 
		return mAnimationStates[mCurrentState].get()->frames[mCurrIdx];
	}

	void SetCurrentState(EAnimationState state)
	{
		if (mCurrentState != state)
		{
			mCurrentState = state;
			mFrameInterval = 0.0f;
			mCurrIdx = 0;
		}
	};

	void AddAnimationState(EAnimationState state, std::shared_ptr<FAnimationData> data)
	{
		mAnimationStates[state] = data;
	}

	CAnimation* Clone() const;

private:
	void Release();
};