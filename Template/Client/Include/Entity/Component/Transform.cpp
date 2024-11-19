#include "Transform.h"

CTransform::~CTransform()
{
    if (mParent)
    {
        CTransform* self = this;
        std::swap(self, mParent->mChilds.back());
        mParent->mChilds.pop_back();
    }

    for (CTransform* child : mChilds)
    {
        SAFE_DELETE(child);
    }
}

void CTransform::AddChild(CTransform* child)
{
    child->mParent = this;
    mChilds.push_back(child);
}