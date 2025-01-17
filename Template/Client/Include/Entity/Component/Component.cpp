#include "Component.h"
#include "Transform.h"

CComponent::CComponent()
{
	mTransform = new CTransform;

	mTransform->mComponent = this;
}

CComponent::~CComponent()
{
	for (size_t i = mChilds.size(); i > 0; i--)
	{
		CComponent* child = mChilds[i - 1];

		std::swap(mChilds[i - 1], mChilds.back());
		mChilds.pop_back();

		child->Release();
	}
	SAFE_DELETE(mTransform);
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
			child->Destroy();

			continue;
		}
		else if (!child->GetEnable())
		{
			continue;
		}
		child->Update(DeltaTime);
	}
}

void CComponent::LateUpdate(float DeltaTime)
{
	for (size_t i = mChilds.size(); i > 0; i--)
	{
		CComponent* child = mChilds[i - 1];

		if (!child->GetActive())
		{
			// Active아닌 component는 마지막 요소랑 바꿔준 후 제거
			std::swap(mChilds[i - 1], mChilds.back());
			mChilds.pop_back();

			child->Release();

			continue;
		}
		else if (!child->GetEnable())
		{
			continue;
		}
		child->LateUpdate(DeltaTime);
	}
}

void CComponent::Render(SDL_Renderer* Renderer)
{
	for (CComponent* child : mChilds)
	{
		if (!child->GetActive() || !child->GetEnable())
			continue;

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

	childToDelete->Release();

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

void CComponent::Enable()
{
	for (CComponent* child : mChilds)
	{
		child->Enable();
	}
	SetEnable(true);
}

void CComponent::Disable()
{
	for (CComponent* child : mChilds)
	{
		child->Disable();
	}
	SetEnable(false);
}

void CComponent::Destroy()
{
	for (CComponent* child : mChilds)
	{
		child->Destroy();
	}
	SetActive(false);
}
