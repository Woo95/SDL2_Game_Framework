#pragma once

#include "../../Core/GameInfo.h"

class CPathManager
{
	friend class CEngine;

private:
	CPathManager();
	~CPathManager();

private:
	static CPathManager* mInst;

	std::unordered_map<std::string, std::string> mPaths;

private:
	bool Init();

public:
	bool AddPath(const std::string& newPathKey, const char* newPathSegment);
	const char* FindPath(const std::string& key);

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