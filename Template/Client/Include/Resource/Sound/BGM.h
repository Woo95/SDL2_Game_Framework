#pragma once

struct Mix_Music;

class CBGM
{
	friend class CSoundManager;

public:
	CBGM();
	~CBGM();

private:
	Mix_Music* mSound = nullptr;
	float mVolume = 0.0f;

public:
	void Play();
	float GetVolume() const;
	void  SetVolume(float volume);

private:
	bool LoadSound(const char* fileName);
};