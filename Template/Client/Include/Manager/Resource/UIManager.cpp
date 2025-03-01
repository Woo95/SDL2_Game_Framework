#include "UIManager.h"

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

const std::vector<SDL_Rect>* const CUIManager::GetUIFrames(const std::string& key)
{
    std::unordered_map<std::string, std::vector<SDL_Rect>>::iterator iter = mUIs.find(key);

    if (iter == mUIs.end())
        return nullptr;

    return &iter->second;
}