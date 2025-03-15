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
	void SetVolume(int volume);

private:
	bool LoadSound(const char* fileName);
};