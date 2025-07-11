#pragma once

#include "../../../Core/GameInfo.h"

class CAssetManager
{
	friend class CGameManager;

private:
	CAssetManager();
	~CAssetManager();

private:
	class CTextureManager*   mTextureManager;
	class CSpriteManager*    mSpriteManager;
	class CAnimationManager* mAnimationManager;
	class CUIManager*        mUIManager;
	class CFontManager*      mFontManager;
	class CSoundManager*     mSoundManager;

	static CAssetManager* mInst;

private:
	bool Init();

public:
	CTextureManager*   GetTextureManager()   const { return mTextureManager; }
	CSpriteManager*    GetSpriteManager()    const { return mSpriteManager; }
	CAnimationManager* GetAnimationManager() const { return mAnimationManager; }
	CUIManager*        GetUIManager()        const { return mUIManager; }
	CFontManager*      GetFontManager()      const { return mFontManager; }
	CSoundManager*     GetSoundManager()     const { return mSoundManager; }


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