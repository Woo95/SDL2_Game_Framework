#pragma once

template <typename T>
class CSharedPtr
{
public:
    CSharedPtr() : 
        mPtr(nullptr)
    {
    }
    CSharedPtr(T* ptr) : 
        mPtr(ptr)
    {
        mPtr->IncrementRef();
    }
    CSharedPtr(const CSharedPtr<T>& other) : 
        mPtr(other.mPtr)
    {
        mPtr->IncrementRef();
    }

    ~CSharedPtr()
    {
        if (mPtr)
            mPtr->DecrementRef();
    }

private:
    T* mPtr;

public:
    void operator = (T* ptr)
    {
        if (mPtr)
            mPtr->DecrementRef();

        mPtr = ptr;

        if (mPtr)
            mPtr->IncrementRef();
    }
    void operator = (const CSharedPtr<T>& other)
    {
        if (mPtr)
            mPtr->DecrementRef();

        mPtr = other.mPtr;

        if (mPtr)
            mPtr->IncrementRef();
    }

    bool operator == (T* ptr) const
    {
        return mPtr == ptr;
    }
    bool operator == (const CSharedPtr<T>& other) const
    {
        return mPtr == other.mPtr;
    }

    bool operator != (T* ptr) const
    {
        return mPtr != ptr;
    }
    bool operator != (const CSharedPtr<T>& other) const
    {
        return mPtr != other.mPtr;
    }

    T* operator -> () const 
    { 
        return mPtr; 
    }
#pragma region conversion operator (형 변환 연산자)
    /*
        // SharedPtr 객체가 T*로 형 변환 해야할때 자동으로 감지 후, 내부 포인터 mPtr을 반환.

        example)
        CSharedPtr<CGameObject> sharedPtr;	// CSharedPtr의 T*는 현재 CGameObject*
        CGameObject* rawPtr = sharedPtr;	// CSharedPtr 객체를 CGameObject*로 형 변환
    */
#pragma endregion
    operator T* () const 
    { 
        return mPtr; 
    }
};