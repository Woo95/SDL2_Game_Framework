#include "Transform.h"

CTransform::CTransform()
{
}

CTransform::~CTransform()
{
    // 부모의 자식 목록에서 자신의 주소 제거
    if (mParent)
    {
        CTransform* self = this;
        std::swap(self, mParent->mChilds.back());
        mParent->mChilds.pop_back();
    }
}

void CTransform::AddChild(CTransform* child)
{
    child->mParent = this;
    mChilds.push_back(child);
}