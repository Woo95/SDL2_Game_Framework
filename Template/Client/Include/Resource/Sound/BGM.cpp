#include "BGM.h"
#include "../../Core/External/SDL/SDL_mixer.h"
#include "../../Manager/Resource/PathManager.h"

CBGM::CBGM()
{
}

CBGM::~CBGM()
{
	if (mSound)
	{
		Mix_FreeMusic(mSound);
		mSound = nullptr;
	}
}

void CBGM::Play()
{ 
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(mSound, -1); // -1: loop
}

void CBGM::SetVolume(int volume)
{
	Mix_VolumeMusic(volume); // 0 ~ 128
}

bool CBGM::LoadSound(const char* fileName)
{
	std::string soundPath = CPathManager::GetInst()->FindPath(SOUND_PATH);
	soundPath += (std::string)fileName;

	mSound = Mix_LoadMUS(soundPath.c_str());

	return mSound != nullptr;
}