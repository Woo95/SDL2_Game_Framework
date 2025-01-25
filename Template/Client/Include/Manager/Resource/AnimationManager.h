#pragma once

#include "../../Core/AniUtils.h"

class CAnimation;

class CAnimationManager
{
    friend class CAssetManager;

private:
    CAnimationManager();
    ~CAnimationManager();

private:
    std::unordered_map<std::string, std::shared_ptr<CAnimation>> mAnimations;

public:
    void CreateAnimation(const std::string& key, EAnimationType type);
    std::shared_ptr<CAnimation> FindAnimation(const std::string& key);
};