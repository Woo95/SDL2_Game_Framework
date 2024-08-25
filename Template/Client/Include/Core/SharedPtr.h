#pragma once

template <typename T>
class CSharedPtr
{
public:
	CSharedPtr()	:
		mPtr(nullptr)
	{
	}

	CSharedPtr(T* Ptr)	:
		mPtr(Ptr)
	{
		mPtr->AddRef();
	}

	CSharedPtr(const CSharedPtr<T>& Ptr)
	{
		mPtr = Ptr.mPtr;
		mPtr->AddRef();
	}

	~CSharedPtr()
	{
		if (mPtr)
			mPtr->Release();
	}
	
private:
	T* mPtr;

public:
	T* Get()	const
	{
		return mPtr;
	}

public:
	void operator = (T* Ptr)
	{
		if (mPtr)
			mPtr->Release();

		mPtr = Ptr;

		if (mPtr)
			mPtr->AddRef();
	}
	void operator = (const CSharedPtr<T>& Ptr)
	{
		if (mPtr)
			mPtr->Release();

		mPtr = Ptr.mPtr;

		if (mPtr)
			mPtr->AddRef();
	}

	T* operator -> ()	const
	{
		return mPtr;
	}
	// conversion operator(형 변환 연산자)
	operator T* ()	const	// SharedPtr 객체가 T*로 형 변환 해야할때 자동으로 감지 후,
	{
		return mPtr;	// 내부 포인터 mPtr을 반환
	}
#pragma region operator T* sample
	/*
		CSharedPtr<CGameObject> sharedPtr;	// CSharedPtr의 T*는 현재 CGameObject*
		CGameObject* rawPtr = sharedPtr;	// CSharedPtr 객체를 CGameObject*로 형 변환
	*/
#pragma endregion

	bool operator == (T* Ptr)	const
	{
		return mPtr == Ptr;
	}
	bool operator == (const CSharedPtr<T>& Ptr)	const
	{
		return mPtr == Ptr.mPtr;
	}

	bool operator != (T* Ptr)	const
	{
		return mPtr != Ptr;
	}
	bool operator != (const CSharedPtr<T>& Ptr)	const
	{
		return mPtr != Ptr.mPtr;
	}
};