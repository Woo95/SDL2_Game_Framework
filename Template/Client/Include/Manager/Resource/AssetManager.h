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
	class CUIManager*        mUIManager;

	static CAssetManager* mInst;

private:
	bool Init();

public:
	CTextureManager*   GetTextureManager()   const { return mTextureManager; }
	CAnimationManager* GetAnimationManager() const { return mAnimationManager; }
	CUIManager*        GetUIManager()        const { return mUIManager; }


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