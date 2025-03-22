#pragma once

#include "../../Core/GameInfo.h"
#include "../../Resource/Sound/SFX.h"
#include "../../Resource/Sound/BGM.h"

template <typename T>
using SoundMap = std::unordered_map<std::string, std::weak_ptr<T>>;

class CSoundManager
{
	friend class CAssetManager;

private:
	CSoundManager();
	~CSoundManager();

private:
	SoundMap<CSFX> mSFXs;
	SoundMap<CBGM> mBGMs;

private:
	bool Init();

public:
	template <typename T>
	std::shared_ptr<T> LoadSound(const std::string& key, const char* fileName)
	{
		std::shared_ptr<T> sound = GetSound<T>(key);

		if (!sound)
		{
			sound = std::make_shared<T>();

			if (sound->LoadSound(fileName))
			{
				GetSoundMap<T>()[key] = sound;
			}
		}
		return sound;
	}

	template <typename T>
	std::shared_ptr<T> GetSound(const std::string& key)
	{
		SoundMap<T>& soundMap = GetSoundMap<T>();

		if (soundMap.find(key) == soundMap.end())
			return nullptr;

		return soundMap[key].lock();
	}

	template <typename T>
	void SetVolume(float volume)
	{
		SoundMap<T>& soundMap = GetSoundMap<T>();

		for (auto& pair : soundMap)
		{
			pair.second.lock()->SetVolume(volume);
		}
	}

	void StopSound();
	void PauseSound();
	void ResumeSound();

private:
	template <typename T>
	std::unordered_map<std::string, std::weak_ptr<T>>& GetSoundMap()
	{
		if constexpr (std::is_same_v<T, CSFX>)
			return mSFXs;
		else if constexpr (std::is_same_v<T, CBGM>)
			return mBGMs;
	}
};
