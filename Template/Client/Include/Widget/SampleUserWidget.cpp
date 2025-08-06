#include "SampleUserWidget.h"
#include "AllWidgets.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Data/Resource/AssetManager.h"
#include "../Manager/Data/Resource/SoundManager.h"

CSampleUserWidget::CSampleUserWidget()
{
    Construct();
}

CSampleUserWidget::~CSampleUserWidget()
{
}

void CSampleUserWidget::Construct()
{    
    // 이미지 생성
    CImage* image = CWidgetUtils::AllocateWidget<CImage>("Image");
    image->GetTransform()->SetRelativeScale(1.0f, 1.0f);
	image->GetTransform()->SetPivot(0.5f, 0.5f);
	image->Set9SlicingCorner(FVector2D(20.0f, 20.0f));
    image->SetCornerRatio(1.5f);
    image->SetTexture("UI");
    image->SetFrame("Panel");
    AddChild(image);

    // 버튼 생성
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("Button");
    button->GetTransform()->SetRelativeScale(0.218f, 0.12f);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("UI");
    button->SetFrame("BlueButton");
    button->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->ChangeRequest(ETransition::SWAP, ESceneState::PLAY); });
    AddChild(button); // 버튼을 패널에 추가

    // 텍스트 블록 생성
    CTextBlock* textBlock = CWidgetUtils::AllocateWidget<CTextBlock>("textBlock");
    textBlock->GetTransform()->SetRelativeScale(0.75f, 0.75f);
    textBlock->GetTransform()->SetPivot(0.5f, 0.5f);
    textBlock->SetFont("Cormorant");
    textBlock->SetText("SAMPLE");
    textBlock->EnableShadow(true);
    button->AddChild(textBlock); // 텍스트를 버튼에 추가

    // 프로그레스 바 생성
    CProgressBar* progressBar = CWidgetUtils::AllocateWidget<CProgressBar>("progressBar");
	progressBar->GetTransform()->SetRelativeScale(0.4f, 0.05f);
	progressBar->GetTransform()->SetRelativePos(0.f, -0.2f);
    progressBar->GetTransform()->SetPivot(0.5f, 0.5f);
    progressBar->SetColor(EProgBar::State::BACK, 0, 0, 0);
    progressBar->SetPercent(0.5f);
    progressBar->SetTexture("UI");
	progressBar->SetFrame("HpBar");
    AddChild(progressBar);

    // 슬라이더 생성
    CSlider* slider = CWidgetUtils::AllocateWidget<CSlider>("Slider");
	slider->GetTransform()->SetRelativeScale(0.4f, 0.05f);
	slider->GetTransform()->SetRelativePos(0.f, 0.2f);
    slider->GetTransform()->SetPivot(0.5f, 0.5f);
    slider->SetTexture("UI");
    slider->SetFrame("Slider");
    slider->SetPercent(0.1f);
    slider->AddCallback(ESlider::InputEvent::HOLD, [](float percent) {CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(percent);});
    AddChild(slider);
}

void CSampleUserWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSampleUserWidget>(this);
}

void CSampleUserWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    HandleDragging(mousePos, isPressed, isHeld, isReleased);
}

void CSampleUserWidget::HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased)
{
}