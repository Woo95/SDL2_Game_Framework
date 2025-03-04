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
}

void CTransform::AddChild(CTransform* child)
{
    child->mParent = this;
    mChilds.push_back(child);
}