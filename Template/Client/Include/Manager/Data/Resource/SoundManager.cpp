#include "SoundManager.h"
#include "../../../Core/External/SDL/SDL_mixer.h"

CSoundManager::CSoundManager()
{
    // 주파수, 포맷, 채널, 버퍼 사이즈
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "CSoundManager Mix_OpenAudio failed: " << Mix_GetError() << "\n";
        throw std::runtime_error("Failed to initialize SDL_mixer");
    }
}

CSoundManager::~CSoundManager()
{
}

void CSoundManager::StopSound()
{
    Mix_HaltChannel(-1); // all sfx
    Mix_HaltMusic();     // bgm
}

void CSoundManager::PauseSound()
{   
    Mix_Pause(-1);    // all sfx
    Mix_PauseMusic(); // bgm
}

void CSoundManager::ResumeSound()
{
    Mix_Resume(-1);    // all sfx
    Mix_ResumeMusic(); // bgm
}