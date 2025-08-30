#pragma once

#include "../../../Core/GameInfo.h"

class CAssetManager
{
	friend class CEngine;

private:
	CAssetManager() = delete;
	CAssetManager(void* memoryBlock);
	~CAssetManager();

private:
	static CAssetManager* mInst;

	class CTextureManager*   mTextureManager;
	class CSpriteManager*    mSpriteManager;
	class CAnimationManager* mAnimationManager;
	class CUIManager*        mUIManager;
	class CFontManager*      mFontManager;
	class CSoundManager*     mSoundManager;

public:
	CTextureManager*   GetTextureManager()   const { return mTextureManager; }
	CSpriteManager*    GetSpriteManager()    const { return mSpriteManager; }
	CAnimationManager* GetAnimationManager() const { return mAnimationManager; }
	CUIManager*        GetUIManager()        const { return mUIManager; }
	CFontManager*      GetFontManager()      const { return mFontManager; }
	CSoundManager*     GetSoundManager()     const { return mSoundManager; }

private:
	template <typename T>
	T* PlacementNew(void*& memoryBlock)
	{
		T* manager = new (memoryBlock) T;
		memoryBlock = (char*)memoryBlock + sizeof(T);

		return manager;
	}
	template <typename T>
	void PlacementDelete(T*& ptr)
	{
		ptr->~T();
		ptr = nullptr;
	}

public:
	static CAssetManager* GetInst();
private:
	static void DestroyInst();
};