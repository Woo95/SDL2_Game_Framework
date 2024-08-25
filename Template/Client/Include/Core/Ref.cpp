#include "Ref.h"

CRef::CRef()
{
}

// 얕은 복사 생성자
CRef::CRef(const CRef& ref)
{
	mTypeID = ref.mTypeID;
	mName = ref.mName;
	mRefCount = 0;
}

CRef::~CRef()
{
}

void CRef::Release()
{
	--mRefCount;

	if (mRefCount == 0)
	{
		delete this;
	}
}

void CRef::AddRef()
{
	++mRefCount;
}
