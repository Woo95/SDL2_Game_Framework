#include "SceneUI.h"
#include "../../Widget/Widget.h"
#include "../../Manager/CollisionManager.h"
#include "../../Core/Input.h"

CSceneUI::CSceneUI()
{
}

CSceneUI::~CSceneUI()
{
	for (CWidget* widget : mWidgets)
	{
		widget->Release();
	}
	mWidgets.clear();
}

bool CSceneUI::Init()
{
	return true;
}

void CSceneUI::Update(float DeltaTime)
{
	UpdateInput();

	for (CWidget* widget : mWidgets)
	{
		if (!widget->GetActive())
		{
			widget->Destroy();

			continue;
		}
		else if (!widget->GetEnable())
		{
			continue;
		}
		widget->Update(DeltaTime);
	}
}

void CSceneUI::LateUpdate(float DeltaTime)
{
	for (CWidget* widget : mWidgets)
	{
		if (!widget->GetActive())
		{
			// mWidgets 벡터의 순서를 유지하면서 widget 제거
			mWidgets.erase(std::remove(mWidgets.begin(), mWidgets.end(), widget), mWidgets.end());
			
			widget->Release();

			continue;
		}
		else if (!widget->GetEnable())
		{
			continue;
		}
		widget->LateUpdate(DeltaTime);
	}
}

void CSceneUI::Render(SDL_Renderer* Renderer)
{
	for (CWidget* widget : mWidgets)
	{
		if (!widget->GetActive() || !widget->GetEnable())
			continue;
		
		widget->Render(Renderer);
	}
}

void CSceneUI::BringWidgetToTop(CWidget* widget)
{
	if (mWidgets.back() == widget || mWidgets.empty() || !widget->mIsInteractable)
		return;

	// mWidgets 벡터의 순서를 유지하면서 widget 제거
	mWidgets.erase(std::remove(mWidgets.begin(), mWidgets.end(), widget), mWidgets.end());
	// 제거했던 widget을 맨 뒤에 추가
	mWidgets.emplace_back(widget);
}

void CSceneUI::SetSceneUI(CWidget* widget)
{
	widget->mSceneUI = this;

	for (CWidget* child : widget->mChilds)
	{
		SetSceneUI(child);
	}
}

CWidget* CSceneUI::FindHoveredWidget(const FVector2D& mousePos)
{
	for (size_t i = mWidgets.size(); i > 0; --i)
	{
		CWidget* hovered = FindHoveredInTree(mWidgets[i - 1], mousePos);

		if (hovered)
			return hovered;
	}
	return nullptr;
}

CWidget* CSceneUI::FindHoveredInTree(CWidget* widget, const FVector2D& mousePos)
{
	if (!CCollisionManager::GetInst()->AABBPointCollision(widget->GetRect(), mousePos))
		return nullptr;

	for (size_t i = widget->mChilds.size(); i > 0; --i) // 렌더링 순서를 고려한 역순 탐색
	{
		CWidget* childHovered = FindHoveredInTree(widget->mChilds[i - 1], mousePos);
		if (childHovered)
			return childHovered;
	}
	return widget->mIsInteractable ? widget : nullptr;
}

void CSceneUI::UpdateInput()
{
	const FVector2D& mousePos = CInput::GetInst()->GetMousePos();

	bool isPressed  = CInput::GetInst()->GetMouseButtonState(SDL_BUTTON_LEFT, EKey::State::PRESS);
	bool isHeld     = CInput::GetInst()->GetMouseButtonState(SDL_BUTTON_LEFT, EKey::State::HOLD);
	bool isReleased = CInput::GetInst()->GetMouseButtonState(SDL_BUTTON_LEFT, EKey::State::RELEASE);

	// 마우스 좌클릭을 홀드 중에, 잡고 있는 Widget이 존재할 경우
	if (mHeldWidget && isHeld)
	{
		// 잡고 있는 Widget의 영역 밖일 경우, Unhovered() 실행
		if (!CCollisionManager::GetInst()->AABBPointCollision(mHeldWidget->GetRect(), mousePos))
		{
			mHeldWidget->HandleUnhovered(mousePos, isHeld, isReleased);
			return; // 잡고 있는 Widget만 처리
		}
	}

	// 마우스 위에 호버된 최상위 Widget 찾기
	CWidget* newHovered = FindHoveredWidget(mousePos);
	{
		// 현재 호버된 mCurrentHovered가 바뀔 경우
		if (mCurrHovered != newHovered)
		{
			// 기존 호버된 Widget이 있다면 HandleUnhovered()를 1회 실행
			if (mCurrHovered)
			{
				mCurrHovered->HandleUnhovered(mousePos, isHeld, isReleased);
			}

			mCurrHovered = newHovered;
		}
		// 호버된 Widget이 있을 경우 HandleHovered() 실행 
		if (mCurrHovered)
			mCurrHovered->HandleHovered(mousePos, isPressed, isHeld, isReleased);
	}
}