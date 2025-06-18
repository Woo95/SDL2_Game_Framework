#include "SoundManager.h"
#include "../../Core/External/SDL/SDL_mixer.h"
#include "../../Resource/Sound/SFX.h"
#include "../../Resource/Sound/BGM.h"

CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
}

bool CSoundManager::Init()
{
    // 주파수, 포맷, 채널, 버퍼 사이즈
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        return false;

    return true;
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