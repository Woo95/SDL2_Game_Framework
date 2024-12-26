#include "Transform.h"

CTransform::CTransform()
{
}

CTransform::~CTransform()
{
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