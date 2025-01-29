#include "Transform.h"

CTransform::CTransform() :
    mWorldPos(FVector2D::ZERO),
    mWorldRotation(0.0f),
    mWorldScale(FVector2D::ZERO),
    mPivot(FVector2D::ZERO),
    mRelativePos(FVector2D::ZERO),
    mRelativeRotation(0.0f),
    mRelativeScale(FVector2D::ZERO)
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