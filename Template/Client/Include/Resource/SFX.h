#pragma once

struct Mix_Chunk;

class CSFX
{
	friend class CSoundManager;

public:
	CSFX();
	~CSFX();

private:
	Mix_Chunk* mSound = nullptr;

public:
	void Play();
	void Stop();
	bool IsPlaying() const;

	void SetVolume(float volume);

private:
	bool LoadSound(const char* fileName);
};