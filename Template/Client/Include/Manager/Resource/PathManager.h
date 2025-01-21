#pragma once

#include "../../Core/GameInfo.h"

class CPathManager
{
private:
	CPathManager();
	~CPathManager();

private:
	std::unordered_map<std::string, std::string> mPaths;

	static CPathManager* mInst;

public:
	bool Init();
	bool AddPath(const std::string& newPathKey, const char* newPathSegment, const std::string& basePathKey = BASE_PATH);
	const char* FindPath(const std::string& name);

public:
	static CPathManager* GetInst()
	{
		if (!mInst)
			mInst = new CPathManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};