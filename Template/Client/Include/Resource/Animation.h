#pragma once

#include "../Core/Utils/AniUtils.h"
#include "../Core/Vector2D.h"

class CTransform;
class CTexture;

class CAnimation
{
	friend class CAnimationManager;
	friend class CSpriteComponent;
	friend class CVFXComponent;

public:
	CAnimation();
	~CAnimation();

protected:
	std::unordered_map<EAnimationState, std::shared_ptr<FAnimationData>> mAnimationStates;
	EAnimationState mCurrentState;

	// for EAnimationType::MOVE //
	CTransform* mTransform;
	FVector2D mPrevPos;

	// for EAnimationType::MOVE & EAnimationType::TIME //
	float mFrameInterval;
	int   mCurrIdx;
	bool  mLooped;

private:
	void Update(float deltaTime);
	void Release();

	CAnimation* Clone() const;

public:
	// 애니메이션 정보
	const SDL_Rect& GetFrame() { return mAnimationStates[mCurrentState].get()->frames[mCurrIdx]; }

	// 루프 상태
	bool GetLooped() const { return mLooped; }
	void ResetLoop() { mLooped = false; }

	// 상태 관련
	void SetState(EAnimationState state)
	{
		if (mCurrentState != state)
		{
			mCurrentState = state;
			mFrameInterval = 0.0f;
			mCurrIdx = 0;
		}
	}
	void AddState(EAnimationState state, std::shared_ptr<FAnimationData> data)
	{
		mAnimationStates[state] = data;
	}
};