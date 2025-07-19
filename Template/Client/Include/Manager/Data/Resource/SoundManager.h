#pragma once

#include "../../../Core/GameInfo.h"
#include "../../../Resource/Sound/SFX.h"
#include "../../../Resource/Sound/BGM.h"

template <typename T> // T 타입을 CSFX 또는 CBGM를 사용하도록 제한
concept SoundType = std::is_same_v<T, CSFX> || std::is_same_v<T, CBGM>;

class CSoundManager
{
	friend class CAssetManager;

private:
	CSoundManager();
	~CSoundManager();

private:
	template <SoundType T>
	using SoundMap = std::unordered_map<std::string, std::weak_ptr<T>>;

	template <SoundType T>
	struct FSoundGroup
	{
		SoundMap<T> soundMap;
		float volume = 0.0f;
	};

	FSoundGroup<CSFX> mSFXs;
	FSoundGroup<CBGM> mBGMs;

public:
	template <SoundType T>
	std::shared_ptr<T> LoadSound(const std::string& key, const char* fileName)
	{
		std::shared_ptr<T> sound = GetSound<T>(key);

		if (!sound)
		{
			sound = std::make_shared<T>();

			if (sound->LoadSound(fileName))
			{
				FSoundGroup<T>& soundGroup = GetSoundGroup<T>();

				sound->SetVolume(soundGroup.volume);
				soundGroup.soundMap[key] = sound;
			}
		}
		return sound;
	}

	template <SoundType T>
	std::shared_ptr<T> GetSound(const std::string& key)
	{
		SoundMap<T>& soundMap = GetSoundGroup<T>().soundMap;

		if (soundMap.find(key) == soundMap.end())
			return nullptr;

		return soundMap[key].lock();
	}

	template <SoundType T>
	float GetVolume()
	{
		return GetSoundGroup<T>().volume;
	}

	template <SoundType T>
	void SetVolume(float volume)
	{
		FSoundGroup<T>& soundGroup = GetSoundGroup<T>();
		soundGroup.volume = volume;

		for (auto& pair : soundGroup.soundMap)
		{
			std::shared_ptr<T> sound = pair.second.lock();
			if (sound)
				sound->SetVolume(soundGroup.volume);
		}
	}

	void StopSound();
	void PauseSound();
	void ResumeSound();

private:
	template <SoundType T>
	FSoundGroup<T>& GetSoundGroup()
	{
		if constexpr (std::is_same_v<T, CSFX>)
			return mSFXs;
		else
			return mBGMs;
	}
};