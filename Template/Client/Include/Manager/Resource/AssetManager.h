#pragma once

#include "../../Core/GameInfo.h"

class CAssetManager
{
private:
	CAssetManager();
	~CAssetManager();

private:
	class CTextureManager*   mTextureManager;
	class CAnimationManager* mAnimationManager;

	static CAssetManager* mInst;

public:
	bool Init();
	void LoadTextures();
	void CreateAnimations();

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