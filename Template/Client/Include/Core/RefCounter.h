#pragma once

class CRefCounter abstract
{
public:
    CRefCounter() = default;
    virtual ~CRefCounter() = default;

private:
    int mRefCount = 0;

private:
    virtual void Release() = 0;

public:
    void IncrementRef()
    {
        mRefCount++;
    }
    void DecrementRef()
    {
        mRefCount--;

        if (mRefCount == 0)
            Release();
    }
};