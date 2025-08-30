#include "UserWidget.h"
#include "../Scene/Extension/SceneUI.h"

CUserWidget::CUserWidget()
{
}

CUserWidget::~CUserWidget()
{
}

void CUserWidget::HandleDragging(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    if (!mIsInteractable || !mIsMovable)
        return;

    if (isPressed)
    {
        mDragOffset = mousePos - GetTransform()->GetWorldPos();
        mSceneUI->BringWidgetToTop(this);
    }
    else if (isHeld && mDragOffset != FVector2D::ZERO)
    {
        FVector2D newPos = mousePos - mDragOffset;
        GetTransform()->SetWorldPos(newPos);
    }
    else if (isReleased)
        mDragOffset = FVector2D::ZERO;
}