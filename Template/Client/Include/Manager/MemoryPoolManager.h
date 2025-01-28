#pragma once

#include <typeindex>
#include <unordered_map>
#include "../Core/StaticMemoryPool.h"

#define	SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

class CMemoryPoolManager
{
private:
	CMemoryPoolManager() = default;
	~CMemoryPoolManager()
	{
		std::unordered_map<std::type_index, IMemoryPool*>::iterator	iter    = mPools.begin();
		std::unordered_map<std::type_index, IMemoryPool*>::iterator	iterEnd = mPools.end();

		for (; iter != iterEnd; iter++)
		{
			SAFE_DELETE(iter->second);
		}
	}

private:
	std::unordered_map<std::type_index, IMemoryPool*> mPools;

	static CMemoryPoolManager* mInst;

public:
	template <typename T>
	bool HasPool() const
	{
		std::type_index key = typeid(T);
		return mPools.count(key) > 0;
	}
	template <typename T>
	bool CreatePool(int initCapacity)
	{
		if (HasPool<T>() || initCapacity <= 0)
			return false;

		std::type_index key = typeid(T);
		mPools[key] = new CStaticMemoryPool<T>(initCapacity);

		return true;
	}
	template <typename T>
	bool DeletePool()
	{
		if (!HasPool<T>())
			return false;

		std::type_index key = typeid(T);
		SAFE_DELETE(mPools[key]);
		mPools.erase(key);

		return true;
	}
	template <typename T>
	T* Allocate()
	{
		if (HasPool<T>())
		{
			CStaticMemoryPool<T>* pool = GetPool<T>();
			return pool->Allocate();
		}
		return nullptr;
	}
	template <typename T>
	void Deallocate(T* deallocPtr)
	{
		if (HasPool<T>())
		{
			CStaticMemoryPool<T>* pool = GetPool<T>();
			pool->Deallocate(deallocPtr);

			if (pool->IsPoolUnused())
			{
				DeletePool<T>();
			}
		}
	}
	template <typename T>
	void DeallocateKeepPool(T* deallocPtr)
	{
		if (HasPool<T>())
		{
			CStaticMemoryPool<T>* pool = GetPool<T>();
			pool->Deallocate(deallocPtr);
		}
	}

private:
	template <typename T>
	CStaticMemoryPool<T>* GetPool()
	{
		std::type_index key = typeid(T);
		return static_cast<CStaticMemoryPool<T>*>(mPools[key]);
	}

public:
	static CMemoryPoolManager* GetInst()
	{
		if (!mInst)
			mInst = new CMemoryPoolManager;
		return mInst;
	}
	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};