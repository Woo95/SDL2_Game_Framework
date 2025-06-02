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

float CBGM::GetVolume() const
{
	return mVolume;
}

void CBGM::SetVolume(float volume)
{
	mVolume = std::clamp(volume, 0.0f, 1.0f);
	int scaledVolume = (int)(mVolume * MIX_MAX_VOLUME);

	Mix_VolumeMusic(scaledVolume);
}

bool CBGM::LoadSound(const char* fileName)
{
	std::string soundPath = CPathManager::GetInst()->FindPath(SOUND_PATH);
	soundPath += (std::string)fileName;

	mSound = Mix_LoadMUS(soundPath.c_str());

	return mSound != nullptr;
}