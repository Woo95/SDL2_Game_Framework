#include "UserWidget.h"
#include "Widget.h"
#include "../Manager/CollisionManager.h"
#include "../Scene/UI/SceneUI.h"

CUserWidget::CUserWidget()
{
    mTransform = new CTransform;
}

CUserWidget::~CUserWidget()
{
    for (CWidget* widget : mWidgets)
    {
        SAFE_DELETE(widget);
    }
    SAFE_DELETE(mTransform);
}

bool CUserWidget::Init()
{
    return true;
}

void CUserWidget::Update(float DeltaTime)
{
    UpdateRect();

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

void CUserWidget::LateUpdate(float DeltaTime)
{
    for (CWidget* widget : mWidgets)
    {
        if (!widget->GetActive())
        {
            // mWidgets 벡터의 순서를 유지하면서 userWidget 제거
            mWidgets.erase(std::remove(mWidgets.begin(), mWidgets.end(), widget), mWidgets.end());

            // transform 벡터의 순서를 유지하면서 transform 제거
            mTransform->mChilds.erase(std::remove(mTransform->mChilds.begin(), mTransform->mChilds.end(), widget->mTransform), mTransform->mChilds.end());

            SAFE_DELETE(widget);

            continue;
        }
        else if (!widget->GetEnable())
        {
            continue;
        }
        widget->LateUpdate(DeltaTime);
    }
}

void CUserWidget::Render(SDL_Renderer* Renderer)
{
#ifdef _DEBUG
    SDL_SetRenderDrawColor(Renderer, 255, 165, 0, 255);
    SDL_RenderDrawRect(Renderer, &mRect);
#endif

    for (CWidget* widget : mWidgets)
    {
    	if (!widget->GetActive() || !widget->GetEnable())
    		continue;
    	
        widget->Render(Renderer);
    }
}

CWidget* CUserWidget::FindWidget(size_t id)
{
    CWidget* foundWidget = nullptr;

    for (CWidget* widget : mWidgets)
    {
        foundWidget = widget->FindWidget(id);

        if (foundWidget)
            break;
    }
    return foundWidget;
}

void CUserWidget::Enable()
{
    SetEnable(true);

    for (CWidget* widget : mWidgets)
    {
        widget->Enable();
    }
}

void CUserWidget::Disable()
{
    SetEnable(false);

    for (CWidget* widget : mWidgets)
    {
        widget->Disable();
    }
}

void CUserWidget::Destroy()
{
    SetActive(false);

    for (CWidget* widget : mWidgets)
    {
        widget->Destroy();
    }
}

void CUserWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    // 마우스 위에 호버된 최상위 Widget 찾기
    CWidget* newHovered = nullptr;
    for (size_t i = mWidgets.size(); i > 0; i--)
    {
        CWidget* widget = mWidgets[i - 1];
        if (CCollisionManager::GetInst()->AABBPointCollision(widget->GetRect(), mousePos))
        {
            newHovered = widget->GetHoveredWidget(mousePos);
            break;
        }
    }

    // 현재 호버된 mCurrentHovered가 바뀔 경우
    if (mCurrHovered != newHovered)
    {
        // 기존 호버된 Widget이 있다면 HandleUnhovered()를 1회 실행
        if (mCurrHovered)
            mCurrHovered->HandleUnhovered();

        mCurrHovered = newHovered;
    }

    // 호버된 Widget이 있을 경우 HandleHovered() 실행 
    if (mCurrHovered)
        mCurrHovered->HandleHovered(isPressed, isHeld, isReleased);

    // 자신의 드래그 이벤트 처리
    HandleDragging(mousePos, isPressed, isHeld, isReleased);
}

void CUserWidget::HandleUnhovered()
{    
    if (mCurrHovered)
        mCurrHovered->HandleUnhovered();
}

void CUserWidget::HandleDragging(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (!mIsMovable || mCurrHovered)
        return;

    if (isPressed)
    {
        mDragOffset = mousePos - GetTransform()->GetWorldPos();
        BringToTop();
    }
    else if (isHeld && mDragOffset != FVector2D::ZERO)
    {
        FVector2D newPos = mousePos - mDragOffset;
        GetTransform()->SetWorldPos(newPos);
    }
    else if (isReleased)
        mDragOffset = FVector2D::ZERO;
}

void CUserWidget::BringToTop()
{
    if (mIsMovable)
        mSceneUI->BringUserWidgetToTop(this);
}