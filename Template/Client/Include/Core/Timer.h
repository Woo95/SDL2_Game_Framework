#pragma once

#include "GameInfo.h"

class CTimer
{
	friend class CGameManager;

private:
	static Uint64 mSecond;
	static Uint64 mTime;
	static float  mDeltaTime;

	static float  mFPS;
	static float  mFPSTime;
	static int    mFPSTick;

public:
	static float GetDeltaTime() { return mDeltaTime; }
	static float GetFPS() { return mFPS; }

private:
	static bool Init();

	static void Update();
	static void UpdateDeltaTime();
	static void UpdateFPS();
};