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

    void LoadAllEntityFrameData();
    void LoadAllEntityAnimationData();
    void LoadAllWidgetData();
};