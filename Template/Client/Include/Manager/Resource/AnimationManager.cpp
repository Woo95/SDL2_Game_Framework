#include "AnimationManager.h"
#include "../../Resource/Animation.h"

CAnimationManager::CAnimationManager()
{
}

CAnimationManager::~CAnimationManager()
{
    mAnimations.clear();
}

void CAnimationManager::CreateAnimation(const std::string& key, EAnimationType type)
{
    std::shared_ptr<CAnimation> animation = FindAnimation(key);

    if (!animation)
    {
        std::shared_ptr<CAnimation> newAnimation = std::make_shared<CAnimation>();

        newAnimation->SetCurrentType(type);

        mAnimations[key] = newAnimation;
    }
}

std::shared_ptr<CAnimation> CAnimationManager::FindAnimation(const std::string& key)
{
    std::unordered_map<std::string, std::shared_ptr<CAnimation>>::iterator iter = mAnimations.find(key);

    if (iter == mAnimations.end())
        return nullptr;

    return iter->second;
}