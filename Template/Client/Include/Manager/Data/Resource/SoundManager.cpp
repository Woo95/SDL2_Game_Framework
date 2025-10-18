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

void CSoundManager::StopSFX()
{
	Mix_HaltChannel(-1); // all sfx
}

void CSoundManager::StopBGM()
{
	Mix_HaltMusic(); // currently playing bgm
}

void CSoundManager::PauseSFX()
{
	Mix_Pause(-1); // all sfx
}

void CSoundManager::PauseBGM()
{
	Mix_PauseMusic(); // currently playing bgm
}

void CSoundManager::ResumeSFX()
{
	Mix_Resume(-1); // all sfx
}

void CSoundManager::ResumeBGM()
{
	Mix_ResumeMusic(); // previously played bgm
}