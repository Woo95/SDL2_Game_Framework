#pragma once

#include "../../Core/GameInfo.h"

class CSFX;
class CBGM;

template <typename T>
using SoundMap = std::unordered_map<std::string, std::shared_ptr<T>>;

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
	bool LoadSound(const std::string& key, const char* fileName)
	{
		SoundMap<T>& soundMap = GetSoundMap<T>();

		if (soundMap.find(key) == soundMap.end())
		{
			std::shared_ptr<T> newSound = std::make_shared<T>();

			if (newSound->LoadSound(fileName))
			{
				soundMap[key] = newSound;
				return true;
			}
		}
		return false;
	}

	template <typename T>
	bool UnloadSound(const std::string& key)
	{
		SoundMap<T>& soundMap = GetSoundMap<T>();

		if (FindSound<T>(key))
		{
			soundMap.erase(key);
			return true;
		}
		return false;
	}

	template <typename T>
	std::shared_ptr<T> FindSound(const std::string& key)
	{
		SoundMap<T>& soundMap = GetSoundMap<T>();

		if (soundMap.find(key) == soundMap.end())
			return nullptr;

		return soundMap[key];
	}

	template <typename T>
	void SetVolume(int volume)
	{
		SoundMap<T>& soundMap = GetSoundMap<T>();

		for (auto& pair : soundMap)
		{
			pair.second.get()->SetVolume(volume);
		}
	}

	void StopSound();
	void PauseSound();
	void ResumeSound();

private:
	template <typename T>
	std::unordered_map<std::string, std::shared_ptr<T>>& GetSoundMap()
	{
		if constexpr (std::is_same_v<T, CSFX>)
			return mSFXs;
		else if constexpr (std::is_same_v<T, CBGM>)
			return mBGMs;
	}
};
