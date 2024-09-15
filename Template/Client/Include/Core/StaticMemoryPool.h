#pragma once

#include <stack>

// Static Memory Pool: 타입별 전용 풀, 크기는 동적(mBlockSize를 기준으로 n개씩)으로 조정
template <typename T>
class CStaticMemoryPool
{
public:
	CStaticMemoryPool(int capacity) :
		mBlockSize(capacity)
	{
		ExpandPool();
	}
	virtual ~CStaticMemoryPool()
	{
		for (T* pool : mMemoryPool)
		{
			SAFE_FREE(pool);
		}
	}

private:
	std::vector<T*> mMemoryPool;
	std::stack<int> mFreeIdx;	// 메모리 풀을 앞쪽부터 사용하게 만들기 위한 스택
	int mBlockSize;

public:
	// 메모리 풀에서 가장 앞쪽의 사용하지 않는 할당된 메모리 영역의 시작 주소를 반환
	T* Allocate()
	{
		if (mFreeIdx.empty())
		{
			ExpandPool();
		}

		int idx = mFreeIdx.top();
		mFreeIdx.pop();

		T* currPool = mMemoryPool[idx / mBlockSize];
		return &currPool[idx % mBlockSize];
	}
	void Deallocate(T* deallocPtr)
	{
		int poolAmount = mMemoryPool.size();
		for (int i = 0; i < poolAmount; i++)
		{
			// 어떤 MemoryPool block에 deallocPtr이 있는지 체크
			if (IsWithinRange(deallocPtr, &mMemoryPool[i][0], &mMemoryPool[i][mBlockSize - 1]))
			{
				int currPoolIdx = deallocPtr - &mMemoryPool[i][0];
				int totalPoolIdx = (mBlockSize * i) + currPoolIdx;
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
		int freeIdx = (mBlockSize * mMemoryPool.size()) - 1;
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