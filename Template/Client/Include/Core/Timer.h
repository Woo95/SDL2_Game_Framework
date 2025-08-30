#pragma once

#include "GameInfo.h"

class CTimer
{
	friend class CEngine;

private:
	CTimer();
	~CTimer();

private:
	static CTimer* mInst;

	Uint64 mTime;
	Uint64 mSecond;
	float  mDeltaTime;

	float  mFPS;
	float  mFPSTime;
	int    mFPSTick;

public:
	float GetDeltaTime() { return mDeltaTime; }
	float GetFPS() { return mFPS; }

private:
	void Update();
	void UpdateDeltaTime();
	void UpdateFPS();

public:
	static CTimer* GetInst()
	{
		if (!mInst)
			mInst = new CTimer;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};