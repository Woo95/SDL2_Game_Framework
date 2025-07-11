#pragma once

#include "../../../Core/Utils/AniUtils.h"

class CAnimation;

class CAnimationManager
{
    friend class CAssetManager;
    friend class CDataLoader;

private:
    CAnimationManager();
    ~CAnimationManager();

private:
    std::unordered_map<std::string, CAnimation*> mAnimations;

public:
    CAnimation* GetAnimation(const std::string& key);

private:
    void CreateAnimation(const std::string& key);
};