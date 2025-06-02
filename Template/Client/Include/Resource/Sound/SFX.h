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
	float mVolume = 0.0f;

public:
	void Play();
	float GetVolume() const;
	void  SetVolume(float volume);

private:
	bool LoadSound(const char* fileName);
};