#pragma once

#include "../../Core/GameInfo.h"

class CUIManager
{
    friend class CAssetManager;
    friend class CDataManager;

private:
    CUIManager();
    ~CUIManager();

private:
    std::unordered_map<std::string, std::vector<SDL_Rect>> mUIs;

public:
    const std::vector<SDL_Rect>* const GetUIFrames(const std::string& key);
};