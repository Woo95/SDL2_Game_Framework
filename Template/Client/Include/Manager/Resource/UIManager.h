#pragma once

#include "../../Core/GameInfo.h"

class CUIManager
{
    friend class CAssetManager;
    friend class CDataManager;

private:
    CUIManager()  = default;
    ~CUIManager() = default;

private:
    std::unordered_map<std::string, std::vector<SDL_Rect>> mUIs;

public:
    const std::vector<SDL_Rect>* const GetUIFrames(const std::string& key)
    {
        std::unordered_map<std::string, std::vector<SDL_Rect>>::iterator iter = mUIs.find(key);

        if (iter == mUIs.end())
            return nullptr;

        return &iter->second;
    }
};