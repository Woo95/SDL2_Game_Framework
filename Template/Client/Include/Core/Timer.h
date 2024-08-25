#pragma once

#include "GameInfo.h"

class CTimer
{
private:
	static Uint64	mSecond;
	static Uint64	mTime;
	static float	mDeltaTime;

	static float	mFPS;
	static float	mFPSTime;
	static int      mFPSTick;
	
private:
	static void DeltaTime();
	static void FPS();

public:
	static float GetDeltaTime()
	{
		return mDeltaTime;
	}

	static float GetFPS()
	{
		return mFPS;
	}

public:
	static bool Init();
	static void Update();
};