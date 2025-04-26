#include "Animation.h"
#include "../Entity/Component/SpriteComponent.h"
#include "../Manager/MemoryPoolManager.h"

CAnimation::CAnimation() :
	mOwner(nullptr),
	mCurrentState(EAnimationState::NONE),
	mPrevPos(FVector2D::ZERO),
	mFrameInterval(0.0f),
	mCurrIdx(0)
{
}

CAnimation::~CAnimation()
{
	std::unordered_map<EAnimationState, std::shared_ptr<FAnimationData>>::iterator iter    = mAnimationStates.begin();
	std::unordered_map<EAnimationState, std::shared_ptr<FAnimationData>>::iterator iterEnd = mAnimationStates.end();

	for (; iter != iterEnd; iter++)
	{
		iter->second = nullptr;
	}
}

void CAnimation::Update(float deltaTime)
{
	FAnimationData* aniData = mAnimationStates[mCurrentState].get();

	switch (aniData->type)
	{
		case EAnimationType::NONE:
			break;

		case EAnimationType::MOVE:
		{
			const FVector2D& currentPos = mOwner->GetTransform()->GetWorldPos();

			FVector2D posDelta = currentPos - mPrevPos;

			mFrameInterval += posDelta.Length();

			float frameTransitionDistance = aniData->intervalPerFrame / aniData->frames.size();

			if (mFrameInterval >= frameTransitionDistance)
			{
				mCurrIdx = (mCurrIdx + 1) % aniData->frames.size();

				mFrameInterval -= frameTransitionDistance;
			}
			mPrevPos = currentPos;
		}
		break;

		case EAnimationType::TIME:
		{
			mFrameInterval += deltaTime;

			if (mFrameInterval >= aniData->intervalPerFrame)
			{
				if (aniData->isLoop)
					mCurrIdx = (mCurrIdx + 1) % aniData->frames.size();
				else
				{
					if (mCurrIdx < aniData->frames.size() - 1)
					{
						mCurrIdx++;
					}
				}
				mFrameInterval = 0.0f;
			}
		}
		break;
	}
}

CAnimation* CAnimation::Clone() const
{
	CAnimation* clone = CMemoryPoolManager::GetInst()->Allocate<CAnimation>();

	*clone = *this; // 얕은 복사

	return clone;
}

void CAnimation::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CAnimation>(this);
}