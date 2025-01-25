#include "Animation.h"
#include "../Entity/Component/Sprite/SpriteComponent.h"

CAnimation::CAnimation()
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Update(float DeltaTime)
{
	FAnimationStateInfo& animation = mAnimationStates[mCurrentState];

	switch (mCurrentType)
	{
		case EAnimationType::NONE:
			break;

		case EAnimationType::MOVE:
		{
			FVector2D currentPos = mOwner->GetTransform()->GetWorldPos();

			static FVector2D prevPos = currentPos;
			FVector2D posDelta = currentPos - prevPos;

			mFrameInterval += posDelta.Length();

			float frameTransitionDistance = animation.IntervalPerFrame / animation.frames.size();

			if (mFrameInterval >= frameTransitionDistance)
			{
				animation.currentIdx = (animation.currentIdx + 1) % animation.frames.size();

				mFrameInterval -= frameTransitionDistance;
			}
			prevPos = currentPos;
		}
		break;

		case EAnimationType::TIME:
		{
			mFrameInterval += DeltaTime;

			if (mFrameInterval >= animation.IntervalPerFrame)
			{
				if (animation.isLoop)
					animation.currentIdx = (animation.currentIdx + 1) % animation.frames.size();
				else
				{
					if (animation.currentIdx < animation.frames.size() - 1)
					{
						animation.currentIdx++;
					}
				}
				mFrameInterval = 0.0f;
			}
		}
		break;
	}
}

void CAnimation::AddFrame(EAnimationState state, SDL_Rect& frame)
{
	mAnimationStates[state].frames.push_back(frame);
}

void CAnimation::AddFrames(EAnimationState state, std::vector<SDL_Rect>& frames)
{
	FAnimationStateInfo& aniInfo = mAnimationStates[state];
	aniInfo.frames.insert(aniInfo.frames.end(), frames.begin(), frames.end());
}