#pragma once

#include "../../../Core/GameInfo.h"

class CSpriteManager
{
    friend class CAssetManager;
    friend class CDataLoader;

private:
    CSpriteManager()  = default;
    ~CSpriteManager() = default;

private:
    std::unordered_map<std::string, SDL_Rect> mSprites;

public:
    const SDL_Rect* const GetSpriteFrame(const std::string& key)
    {
        std::unordered_map<std::string, SDL_Rect>::iterator iter = mSprites.find(key);

        if (iter == mSprites.end())
            return nullptr;

        return &iter->second;
    }
};