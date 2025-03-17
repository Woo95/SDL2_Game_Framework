#include "Widget.h"
#include "UserWidget.h"
#include "../Manager/CollisionManager.h"
#include "../Scene/UI/SceneUI.h"
#include "../Manager/MemoryPoolManager.h"

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

void CWidget::Update(float DeltaTime)
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
		child->Update(DeltaTime);
	}
}

void CWidget::LateUpdate(float DeltaTime)
{
	for (CWidget* child : mChilds)
	{
		if (!child->GetActive())
		{
			// mWidgets 벡터의 순서를 유지하면서 userWidget 제거
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
		child->LateUpdate(DeltaTime);
	}
}

void CWidget::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
	for (CWidget* child : mChilds)
	{
		if (!child->GetActive() || !child->GetEnable())
			continue;

		child->Render(Renderer, topLeft);
	}

#ifdef _DEBUG
	SDL_Rect renderRect = mRect;

	renderRect.x += (int)topLeft.x;
	renderRect.y += (int)topLeft.y;

	SDL_SetRenderDrawColor(Renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(Renderer, &renderRect);
#endif
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
	child->mUserWidget = mUserWidget;
	child->mParent = this;

	mChilds.emplace_back(child);

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

void CWidget::Enable()
{
	for (CWidget* child : mChilds)
	{
		child->Enable();
	}
	SetEnable(true);
}

void CWidget::Disable()
{
	for (CWidget* child : mChilds)
	{
		child->Disable();
	}
	SetEnable(false);
}

void CWidget::Destroy()
{
	for (CWidget* child : mChilds)
	{
		child->Destroy();
	}
	SetActive(false);
}

CWidget* CWidget::GetHoveredWidget(const FVector2D& mousePos)
{
	if (!CCollisionManager::GetInst()->AABBPointCollision(GetRect(), mousePos))
		return nullptr;

	for (size_t i = mChilds.size(); i > 0; i--)
	{
		CWidget* childHovered = mChilds[i - 1]->GetHoveredWidget(mousePos);

		if (childHovered)
			return childHovered;
	}
	return mIsTriggerable ? this : nullptr;
}

void CWidget::ExecuteCallback(EWidgetInput::Event event)
{
	if (!mEventCallbacks.count(event))
		return;

	for (auto& callback : mEventCallbacks[event])
	{
		callback();
	}
}