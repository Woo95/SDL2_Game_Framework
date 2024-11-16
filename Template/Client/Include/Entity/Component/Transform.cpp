#include "Transform.h"

void CTransform::AddChild(CTransform* child)
{
	child->mParent = this;
	mChilds.push_back(child);
}

void CTransform::DeleteChild(CTransform* child)
{
	std::swap(child, mChilds.back());
	mChilds.pop_back();
}