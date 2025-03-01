#include "AnimationManager.h"
#include "../../Resource/Animation.h"
#include "../MemoryPoolManager.h"

CAnimationManager::CAnimationManager()
{
    CMemoryPoolManager::GetInst()->CreatePool<CAnimation>(100);
}

CAnimationManager::~CAnimationManager()
{
    std::unordered_map<std::string, CAnimation*>::iterator iter    = mAnimations.begin();
    std::unordered_map<std::string, CAnimation*>::iterator iterEnd = mAnimations.end();

    for (; iter != iterEnd; iter++)
    {
        (iter->second)->Release();
    }
    CMemoryPoolManager::GetInst()->DeletePool<CAnimation>();
}

CAnimation* CAnimationManager::GetAnimation(const std::string& key)
{
    std::unordered_map<std::string, CAnimation*>::iterator iter = mAnimations.find(key);

    if (iter == mAnimations.end())
        return nullptr;

    return iter->second;
}

void CAnimationManager::CreateAnimation(const std::string& key)
{
    CAnimation* animation = GetAnimation(key);

    if (!animation)
    {
        CAnimation* newAnimation = CMemoryPoolManager::GetInst()->Allocate<CAnimation>();

        mAnimations[key] = newAnimation;
    }
}