#pragma once

#include <stack>

#define	SAFE_FREE(p) if(p) { free(p); p = nullptr; }

/* CMemoryPoolManager은 CStaticMemoryPool을 T 타입에 대한 정보 없이 void*로 관리할 수 없다.
   void*일 경우 CStaticMemoryPool의 소멸자도 호출 할 수 없다. 이를 해결하기 위해 IMemoryPool 인터페이스를 상속받아서 void* 대신 사용한다. */
class IMemoryPool abstract
{
	friend class CMemoryPoolManager;

public:
	virtual ~IMemoryPool() = default;
};

// Static Memory Pool: 타입별 전용 풀, 크기는 동적(mBlockSize를 기준으로 n개씩)으로 조정
template <typename T>
class CStaticMemoryPool : public IMemoryPool
{
	friend class CMemoryPoolManager;

private:
	CStaticMemoryPool(int capacity) :
		mBlockSize(capacity)
	{
		ExpandPool();
	}
	virtual ~CStaticMemoryPool()
	{
		size_t poolAmount = mMemoryPool.size();
		for (size_t i = 0; i < poolAmount; i++)
		{
			SAFE_FREE(mMemoryPool[i]);
		}
	}

private:
	std::vector<T*> mMemoryPool;
	std::stack<size_t> mFreeIdx;	// 메모리 풀을 앞쪽부터 사용하게 만들기 위한 스택
	int mBlockSize;

private:
	// 메모리 풀에서 가장 앞쪽의 사용하지 않는 할당된 메모리 영역의 시작 주소를 반환
	T* Allocate()
	{
		if (mFreeIdx.empty())
		{
			ExpandPool();
		}

		size_t idx = mFreeIdx.top();
		mFreeIdx.pop();

		T* currPool = mMemoryPool[idx / mBlockSize];
		// placement new는 "이미 할당된" 메모리 블록 내에서 객체를 생성하고 초기화한다. (즉 메모리 할당을 제외한 모든 것이 new와 동일하다)
		T* obj = new (&currPool[idx % mBlockSize]) T;	// 객체 생성 시 vtable이 자동 설정되어 가상 함수 호출이 정상 동작한다.
		
		return obj;
	}
	void Deallocate(T* deallocPtr)
	{
		// placement new로 생성된 객체는 소멸자를 명시적으로 호출하여, 객체의 메모리는 그대로 두고 객체만 정리한다.
		deallocPtr->~T();

		size_t poolAmount = mMemoryPool.size();
		for (size_t i = 0; i < poolAmount; i++)
		{
			// 어떤 MemoryPool block에 deallocPtr이 있는지 체크
			if (IsWithinRange(deallocPtr, &mMemoryPool[i][0], &mMemoryPool[i][mBlockSize - 1]))
			{
				size_t currPoolIdx = deallocPtr - &mMemoryPool[i][0];
				size_t totalPoolIdx = (mBlockSize * i) + currPoolIdx;
				mFreeIdx.push(totalPoolIdx);

				deallocPtr = nullptr;
				break;
			}
		}
	}

private:
	void ExpandPool()
	{
		// allocate or reallocate memory
		T* newPool = (T*)malloc(sizeof(T) * mBlockSize);
		mMemoryPool.push_back(newPool);

		// update mFreeIdx
		size_t freeIdx = (mBlockSize * mMemoryPool.size()) - 1;
		for (int i = 0; i < mBlockSize; i++)
		{
			mFreeIdx.push(freeIdx - i);
		}
	}
	bool IsWithinRange(T* ptr, T* start, T* end) const
	{
		return ptr >= start && ptr <= end;
	}
};