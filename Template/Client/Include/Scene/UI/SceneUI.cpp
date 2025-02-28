#include "SceneUI.h"
#include "../../Widget/UserWidget.h"
#include "../../Manager/CollisionManager.h"
#include "../../Core/Input.h"

CSceneUI::CSceneUI()
{
}

CSceneUI::~CSceneUI()
{
	for (CUserWidget* userWidget : mUserWidgets)
	{
		SAFE_DELETE(userWidget);
	}
}

bool CSceneUI::Init()
{
	return true;
}

void CSceneUI::Update(float DeltaTime)
{
	UpdateInput();

	for (CUserWidget* userWidget : mUserWidgets)
	{
		userWidget->Update(DeltaTime);
	}
}

void CSceneUI::LateUpdate(float DeltaTime)
{
	for (CUserWidget* userWidget : mUserWidgets)
	{
		userWidget->LateUpdate(DeltaTime);
	}
}

void CSceneUI::Render(SDL_Renderer* Renderer)
{
	for (CUserWidget* userWidget : mUserWidgets)
	{
		userWidget->Render(Renderer);
	}
}

CUserWidget* CSceneUI::FindUserWidget(const std::string& name)
{
	size_t hashID = std::hash<std::string>()(name);

	for (CUserWidget* userWidget : mUserWidgets)
	{
		if (userWidget->GetID() == hashID)
			return userWidget;
	}
	return nullptr;
}

void CSceneUI::UpdateInput()
{
	const FVector2D& mousePos = CInput::GetInst()->GetMousePos();

	bool isPressed  = CInput::GetInst()->GetMouseButtonState(SDL_BUTTON_LEFT, EKey::State::PRESS);
	bool isHeld     = CInput::GetInst()->GetMouseButtonState(SDL_BUTTON_LEFT, EKey::State::HOLD);
	bool isReleased = CInput::GetInst()->GetMouseButtonState(SDL_BUTTON_LEFT, EKey::State::RELEASE);

	// 마우스 위에 호버된 최상위 UserWidget 찾기
    CUserWidget* newHovered = nullptr;
    for (size_t i = mUserWidgets.size(); i > 0; i--)
    {
        CUserWidget* userWidget = mUserWidgets[i - 1];
        if (CCollisionManager::GetInst()->AABBPointCollision(userWidget->GetRect(), mousePos))
        {
            newHovered = userWidget;
            break;
        }
    }
	// 현재 호버된 mCurrentHovered가 바뀔 경우
	if (mCurrHovered != newHovered)
	{
		// 기존 호버된 userWidget이 있다면 HandleUnhovered()를 1회 실행
		if (mCurrHovered)
			mCurrHovered->HandleUnhovered();

		mCurrHovered = newHovered;
	}
	// 호버된 userWidget이 있을 경우 HandleHovered() 실행 
    if (mCurrHovered)
        mCurrHovered->HandleHovered(mousePos, isPressed, isHeld, isReleased);


	// 마우스 좌클릭을 떼었을 때, 잡고 있던 Widget 해제
	if (mHeldWidget && isReleased)
		mHeldWidget = nullptr;
}

void CSceneUI::BringUserWidgetToTop(CUserWidget* userWidget)
{
	if (mUserWidgets.back() == userWidget || mUserWidgets.empty())
		return;

	mUserWidgets.erase(std::remove(mUserWidgets.begin(), mUserWidgets.end(), userWidget), mUserWidgets.end());
	mUserWidgets.emplace_back(userWidget);
}