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

public:
	void Play();
	void SetVolume(int volume);

private:
	bool LoadSound(const char* fileName);
};