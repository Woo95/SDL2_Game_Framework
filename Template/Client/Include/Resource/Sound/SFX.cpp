#include "SFX.h"
#include "../../Core/External/SDL/SDL_mixer.h"
#include "../../Manager/Resource/PathManager.h"

CSFX::CSFX()
{
}

CSFX::~CSFX()
{
	if (mSound)
	{
		Mix_FreeChunk(mSound);
		mSound = nullptr;
	}
}

void CSFX::Play()
{ 
	// 첫번째 인자 (-1): play on the first free channel
	// 세번째 인자  (0): don't loop
	Mix_PlayChannel(-1, mSound, 0);
}

void CSFX::SetVolume(int volume)
{
	Mix_VolumeChunk(mSound, volume);
}

bool CSFX::LoadSound(const char* fileName)
{
	std::string soundPath = CPathManager::GetInst()->FindPath(SOUND_PATH);
	soundPath += (std::string)fileName;

	mSound = Mix_LoadWAV(soundPath.c_str());

	return mSound != nullptr;
}
