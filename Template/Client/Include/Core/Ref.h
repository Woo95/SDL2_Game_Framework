#pragma once

#include "GameInfo.h"

class CRef
{
public:
	CRef();
	CRef(const CRef& ref);
	virtual ~CRef();	// 가상 함수로 만들면 재정의를 해줄 경우, 가상 함수 테이블에 재정의를 해준 소멸자가 등록이 되어서 호출된다.

protected:
	std::string	mName;
	int		mRefCount = 0;
	size_t	mTypeID = 0;
	bool	mActive = true;
	bool	mEnable = true;

public:	// getter
	bool GetActive()	const
	{
		return mActive;
	}

	bool GetEnable()	const
	{
		return mEnable;
	}

	const std::string& GetName()	const
	{
		return mName;
	}

public:	// setter
	void SetName(const std::string& Name)
	{
		mName = Name;
	}

	void SetEnable(bool Enable)
	{
		mEnable = Enable;
	}

	void SetActive(bool Active)
	{
		mActive = Active;
	}

	void Release();
	void AddRef();

public:
	template <typename T>
	bool CompareType()
	{
		return mTypeID == typeid(T).hash_code();
	}

protected:
	template <typename T>
	void SetType()
	{
		mTypeID = typeid(T).hash_code();
	}
};

