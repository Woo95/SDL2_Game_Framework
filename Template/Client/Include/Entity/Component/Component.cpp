#include "Component.h"
#include "Transform.h"

CComponent::CComponent()
{
	mTransform = new CTransform;

	mTransform->mComponent = this;
}

CComponent::~CComponent()
{
	for (CComponent* child : mChilds)
	{
		std::swap(child, mChilds.back());
		mChilds.pop_back();

		mTransform->DeleteChild(child->mTransform);
		if (!child->Release())
		{
			SAFE_DELETE(child);
		}
	}
	SAFE_DELETE(mTransform)
}

bool CComponent::Init()
{
	for (CComponent* child : mChilds)
	{
		if (!child->Init())
			return false;
	}
	return true;
}

void CComponent::Update(float DeltaTime)
{
	for (CComponent* child : mChilds)
	{
		if (!child->GetActive())
		{
			// Active아닌 component는 마지막 요소랑 바꿔준 후 제거
			std::swap(child, mChilds.back());
			mChilds.pop_back();

			DeleteChild(child);
			continue;
		}
		else if (!child->GetEnable())
		{
			continue;
		}
		child->Update(DeltaTime);
	}
}

void CComponent::Render(SDL_Renderer* Renderer)
{
	for (CComponent* child : mChilds)
	{
		if (!child->GetActive())
		{
			// Active아닌 component는 마지막 요소랑 바꿔준 후 제거
			std::swap(child, mChilds.back());
			mChilds.pop_back();

			DeleteChild(child);
			continue;
		}
		else if (!child->GetEnable())
		{
			continue;
		}
		child->Render(Renderer);
	}
}

void CComponent::AddChild(CComponent* child)
{
    child->mParent = this;
    mChilds.push_back(child);

    mTransform->AddChild(child->mTransform);
}

// 직속 자식 관계일 경우만 삭제
bool CComponent::DeleteChild(CComponent* child)
{
	CComponent* childToDelete = FindComponent(child->mID);

	if (!childToDelete)
		return false;
	
	mTransform->DeleteChild(childToDelete->mTransform);
	if (!childToDelete->Release())
	{
		SAFE_DELETE(childToDelete);
	}

	return true;
}

CComponent* CComponent::FindComponent(size_t id)
{
    if (mID == id)
        return this;

	for (CComponent* child : mChilds)
	{
		CComponent* foundComp = child->FindComponent(id);

		if (foundComp)
			return foundComp;
	}
	return nullptr;
}