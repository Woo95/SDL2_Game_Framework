#pragma once

#include "../../Core/GameInfo.h"

class CAssetManager
{
private:
	CAssetManager();
	~CAssetManager();

private:
	class CTextureManager* mTextureManager;

	static CAssetManager* mInst;

public:
	bool Init();

public:
	static CAssetManager* GetInst()
	{
		if (!mInst)
			mInst = new CAssetManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};