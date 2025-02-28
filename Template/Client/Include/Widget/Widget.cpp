#include "Widget.h"
#include "UserWidget.h"
#include "../Manager/CollisionManager.h"
#include "../Scene/UI/SceneUI.h"

CWidget::CWidget()
{
	mTransform = new CTransform;
}

CWidget::~CWidget()
{
	for (CWidget* child : mChilds)
	{
		SAFE_DELETE(child);
	}
	SAFE_DELETE(mTransform);
}

bool CWidget::Init()
{
	for (CWidget* child : mChilds)
	{
		if (!child->Init())
			return false;
	}
	return true;
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
	for (size_t i = mChilds.size(); i > 0; i--)
	{
		CWidget* child = mChilds[i - 1];

		if (!child->GetActive())
		{
			// Active아닌 component는 마지막 요소랑 바꿔준 후 제거
			std::swap(mChilds[i - 1], mChilds.back());
			mChilds.pop_back();

			SAFE_DELETE(child);

			continue;
		}
		else if (!child->GetEnable())
		{
			continue;
		}
		child->LateUpdate(DeltaTime);
	}
}

void CWidget::Render(SDL_Renderer* Renderer)
{
#ifdef _DEBUG
	SDL_SetRenderDrawColor(Renderer, 255, 255, 0, 255);
	SDL_RenderDrawRect(Renderer, &mRect);
#endif

	for (CWidget* child : mChilds)
	{
		if (!child->GetActive() || !child->GetEnable())
			continue;

		child->Render(Renderer);
	}
}

void CWidget::AddChild(CWidget* child)
{
	child->mUserWidget = mUserWidget;
	child->mParent = this;

	mChilds.emplace_back(child);
	child->SetZOrder(GetZOrder() + 1);

	mTransform->AddChild(child->mTransform);
}

// 직속 자식 관계일 경우만 삭제
bool CWidget::DeleteChild(CWidget* child)
{
	CWidget* childToDelete = FindWidget(child->mID);

	if (!childToDelete)
		return false;

	SAFE_DELETE(childToDelete);

	return true;
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

void CWidget::HandleHovered(bool isPressed, bool isHeld, bool isReleased)
{
	if (!mIsTriggerable)
		return;

	// 만약 잡혀 있는 위젯이 존재하고, 현재 위젯이 아니면 처리하지 않음
	CWidget* currHeld = mUserWidget->mSceneUI->GetHeldWidget();
	if (currHeld && currHeld != this)
		return;

	// 위젯 최초로 호버할 때 처리
	if (!mMouseHovered)
	{
		mMouseHovered = true;

		if (currHeld == this)
			ExecuteCallback(EWidgetInput::Event::HOLD);
		else
			ExecuteCallback(EWidgetInput::Event::HOVER);
	}
	// 위젯 호버 중일 때 처리
	else
	{
		if (isPressed && !currHeld)
		{
			mUserWidget->BringToTop();
			mUserWidget->mSceneUI->SetHeldWidget(this);
			ExecuteCallback(EWidgetInput::Event::CLICK);
		}
		else if (isHeld && currHeld == this)
		{
			ExecuteCallback(EWidgetInput::Event::HOLD);
		}
		else if (isReleased && currHeld == this)
		{
			mUserWidget->mSceneUI->SetHeldWidget(nullptr);
			ExecuteCallback(EWidgetInput::Event::RELEASE);
		}
	}
}

void CWidget::HandleUnhovered()
{
	if (mMouseHovered)
	{
		mMouseHovered = false;
		ExecuteCallback(EWidgetInput::Event::UNHOVER);
	}
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