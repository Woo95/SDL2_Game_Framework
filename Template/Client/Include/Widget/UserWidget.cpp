#include "UserWidget.h"
#include "Widget.h"
#include "../Manager/CollisionManager.h"
#include "../Scene/UI/SceneUI.h"
#include "../Manager/MemoryPoolManager.h"

CUserWidget::CUserWidget()
{
    mTransform = CMemoryPoolManager::GetInst()->Allocate<CTransform>();
}

CUserWidget::~CUserWidget()
{
    CMemoryPoolManager::GetInst()->DeallocateButKeepPool<CTransform>(mTransform);

    for (CWidget* widget : mWidgets)
    {
        widget->Release();
    }
    mWidgets.clear();
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
            mTransform->GetChilds().erase(std::remove(mTransform->GetChilds().begin(), mTransform->GetChilds().end(), widget->mTransform), mTransform->GetChilds().end());

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

void CUserWidget::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
    for (CWidget* widget : mWidgets)
    {
        if (!widget->GetActive() || !widget->GetEnable())
            continue;

        widget->Render(Renderer, topLeft);
    }

#ifdef _DEBUG
    SDL_Rect renderRect = mRect;

    renderRect.x += (int)topLeft.x;
    renderRect.y += (int)topLeft.y;

    SDL_SetRenderDrawColor(Renderer, 255, 165, 0, 255);
    SDL_RenderDrawRect(Renderer, &renderRect);
#endif
}

void CUserWidget::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CUserWidget>(this);
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

CWidget* CUserWidget::FindHoveredWidget(const FVector2D& mousePos)
{
    for (size_t i = mWidgets.size(); i > 0; i--)
    {
        CWidget* newHovered = mWidgets[i - 1];
        if (CCollisionManager::GetInst()->AABBPointCollision(newHovered->GetRect(), mousePos))
        {
            return newHovered->FindHoveredWidget(mousePos);
        }
    }
    return nullptr;
}

void CUserWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    // 마우스 위에 호버된 최상위 Widget 찾기
    CWidget* newHovered = FindHoveredWidget(mousePos);
    {
        // 현재 호버된 mCurrentHovered가 바뀔 경우
        if (mCurrHovered != newHovered)
        {
            // 기존 호버된 Widget이 있다면 HandleUnhovered()를 1회 실행
            if (mCurrHovered)
                mCurrHovered->HandleUnhovered(mousePos, isHeld, isReleased);

            mCurrHovered = newHovered;
        }
        // 호버된 Widget이 있을 경우 HandleHovered() 실행 
        if (mCurrHovered)
            mCurrHovered->HandleHovered(mousePos, isPressed, isHeld, isReleased);
    }

    // 자신의 드래그 이벤트 처리
    HandleDragging(mousePos, isPressed, isHeld, isReleased);
}

void CUserWidget::HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased)
{    
    if (mCurrHovered)
        mCurrHovered->HandleUnhovered(mousePos, isHeld, isReleased);
}

void CUserWidget::HandleDragging(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (!mIsMovable || mCurrHovered)
        return;

    if (isPressed)
    {
        mDragOffset = mousePos - GetTransform()->GetWorldPos();
        mSceneUI->BringUserWidgetToTop(this);
    }
    else if (isHeld && mDragOffset != FVector2D::ZERO)
    {
        FVector2D newPos = mousePos - mDragOffset;
        GetTransform()->SetWorldPos(newPos);
    }
    else if (isReleased)
        mDragOffset = FVector2D::ZERO;
}