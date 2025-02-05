#pragma once

#include "../../Core/AniUtils.h"

class CAnimation;

class CAnimationManager
{
    friend class CAssetManager;
    friend class CDataManager;

private:
    CAnimationManager();
    ~CAnimationManager();

private:
    std::unordered_map<std::string, CAnimation*> mAnimations;

public:
    CAnimation* FindAnimation(const std::string& key);

private:
    void CreateAnimation(const std::string& key);
};