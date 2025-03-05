#pragma once

#include "../../Core/GameInfo.h"

class CDataManager
{
    friend class CAssetManager;

private:
    CDataManager();
    ~CDataManager();

private:
    bool Init();

    std::vector<std::string> Split(const std::string& line, char delimiter);

    void LoadAllSpriteData();
    void LoadAllAnimationData();
    void LoadAllButtonData();
    void LoadAllImageData();
};