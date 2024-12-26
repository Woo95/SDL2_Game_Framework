#pragma once

#include "../Core/GameInfo.h"
#include "../Core/DataContainer.h"

class CMemoryReleaseManager
{
public:
	CMemoryReleaseManager();
	~CMemoryReleaseManager();

private:
	std::vector<DataContainer*> mGarbage;

	static CMemoryReleaseManager* mInst;

public:
	void Update(float DeltaTime);

public:
	template <typename T>
	void AddGarbage(T* garbage)
	{
		mGarbage.push_back((DataContainer*)garbage);
	}

public:
	static CMemoryReleaseManager* GetInst()
	{
		if (!mInst)
			mInst = new CMemoryReleaseManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};