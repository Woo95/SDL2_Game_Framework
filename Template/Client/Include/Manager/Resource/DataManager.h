#pragma once

#include "../../Core/GameInfo.h"

class CDataManager
{
    friend class CAssetManager;

private:
    CDataManager();
    ~CDataManager();

private:
    std::vector<std::string> Split(const std::string& line, char delimiter);

public:
    void LoadAllAnimationData();
    void LoadAllUIData();

private:
    void LoadAllButtonData();
};