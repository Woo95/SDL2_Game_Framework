#pragma once

#include "../../Core/GameInfo.h"

class CAssetManager
{
	friend class CGameManager;

private:
	CAssetManager();
	~CAssetManager();

private:
	class CDataManager*      mDataManager;

	class CTextureManager*   mTextureManager;
	class CAnimationManager* mAnimationManager;

	static CAssetManager* mInst;

private:
	bool Init();

public:
	void LoadTextures();

	CTextureManager*   GetTextureManager()   const { return mTextureManager; }
	CAnimationManager* GetAnimationManager() const { return mAnimationManager; }

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