#include "Widget.h"

CWidget::CWidget()
{
	mTransform = CMemoryPoolManager::GetInst()->Allocate<CTransform>();
}

CWidget::~CWidget()
{
	CMemoryPoolManager::GetInst()->DeallocateButKeepPool<CTransform>(mTransform);

	for (CWidget* child : mChilds)
	{
		child->Release();
	}
	mChilds.clear();
}

void CWidget::Update(float deltaTime)
{
	UpdateRect();

	for (CWidget* child : mChilds)
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
		child->Update(deltaTime);
	}
}

void CWidget::LateUpdate(float deltaTime)
{
	for (CWidget* child : mChilds)
	{
		if (!child->GetActive())
		{
			// mWidgets 벡터의 순서를 유지하면서 widget 제거
			mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), child), mChilds.end());

			// transform 벡터의 순서를 유지하면서 transform 제거
			mTransform->GetChilds().erase(std::remove(mTransform->GetChilds().begin(), mTransform->GetChilds().end(), child->mTransform), mTransform->GetChilds().end());

			child->Release();

			continue;
		}
		else if (!child->GetEnable())
		{
			continue;
		}
		child->LateUpdate(deltaTime);
	}
}

void CWidget::Render(SDL_Renderer* renderer, const FVector2D& topLeft)
{
	for (CWidget* child : mChilds)
	{
		if (!child->GetActive() || !child->GetEnable())
			continue;

		child->Render(renderer, topLeft);
	}

#ifdef _DEBUG
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &renderRect);
#endif
}

CWidget* CWidget::FindRootWidget()
{
	CWidget* rootWidget = this;

	while (rootWidget->mParent)
	{
		rootWidget = rootWidget->mParent;
	}
	return rootWidget;
}

CWidget* CWidget::FindWidget(size_t id)
{
	if (mID == id)
		return this;

	for (CWidget* child : mChilds)
	{
		CWidget* foundWidget = child->FindWidget(id);

		if (foundWidget)
			return foundWidget;
	}
	return nullptr;
}

void CWidget::AddChild(CWidget* child)
{
	mChilds.emplace_back(child);

	child->mSceneUI = FindRootWidget()->mSceneUI;
	child->mParent = this;

	mTransform->AddChild(child->mTransform);
}

// 직속 자식 관계일 경우만 삭제
bool CWidget::DeleteChild(CWidget* child)
{
	CWidget* childToDelete = FindWidget(child->mID);

	if (!childToDelete)
		return false;

	childToDelete->Release();

	return true;
}

void CWidget::Destroy()
{
	for (CWidget* child : mChilds)
	{
		child->Destroy();
	}
	SetActive(false);
}